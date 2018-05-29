/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <Box2D/Box2D.h>
#include <iostream>

#include "Physics.h"
#include "Player.h"
#include "PlayerBackFlipping.h"
#include "PlayerEndBackFlip.h"
#include "PlayerEndJump.h"
#include "PlayerJumping.h"
#include "PlayerStartBackFlip.h"
#include "PlayerStartJump.h"
#include "PlayerStill.h"
#include "PlayerWalk.h"
#include "Hit.h"
#include "Die.h"
#include "Dead.h"
#include "Drown.h"

Worms::Player::Player(Physics &physics) : PhysicsEntity(Worms::EntityID::EtWorm), physics(physics) {
    this->bodyDef.type = b2_dynamicBody;
    this->bodyDef.position.Set(0.0f, 0.0f);
    this->bodyDef.fixedRotation = true;

    this->body = this->physics.createBody(this->bodyDef);
    this->shape.SetAsBox(PLAYER_WIDTH / 2, PLAYER_HEIGHT / 2);
    this->fixture.shape = &this->shape;
    this->fixture.density = 1.0f;
    this->fixture.restitution = 0.1f;
    this->fixture.friction = 0.0f;

    this->body->CreateFixture(&this->fixture);
    this->body->SetUserData(this);

    this->state = std::shared_ptr<State>(new Still());
    this->direction = Direction::left;

    this->setState(Worm::StateID::Still);
}

void Worms::Player::update(float dt) {
    this->state->update(*this, dt, this->body);
    this->weapon.update(dt);
    if (this->bullet != nullptr) {
        this->bullet->update(dt);
//        if (this->bullet->madeImpact()) {
//            this->bullet = nullptr;
//        }
        if (this->bullet->getPosition().y < -2) {
            this->bullet = nullptr;
        }
    }
    if (this->getPosition().y <= -2 && this->numContacts == 0
        && this->getStateId() != Worm::StateID::Dead
        && this->getStateId() != Worm::StateID::Drown) {
        this->health = 0.0f;
        this->setState(Worm::StateID::Drown);
    }
}

void Worms::Player::setPosition(const Math::Point<float> &new_pos) {
    this->body->SetTransform(b2Vec2(new_pos.x, new_pos.y), body->GetAngle());
}

Math::Point<float> Worms::Player::getPosition() const {
    const b2Vec2 &pos = this->body->GetPosition();
    return Math::Point<float>{pos.x, pos.y};
}

Worm::StateID Worms::Player::getStateId() const {
    return this->state->getState();
}

void Worms::Player::handleState(IO::PlayerInput pi) {
    switch (pi) {
        case IO::PlayerInput::moveLeft:
            this->state->moveLeft(*this);
            break;
        case IO::PlayerInput::moveRight:
            this->state->moveRight(*this);
            break;
        case IO::PlayerInput::startJump:
            this->state->jump(*this);
            break;
        case IO::PlayerInput::startBackFlip:
            this->state->backFlip(*this);
            break;
        case IO::PlayerInput::stopMove:
            this->state->stopMove(*this);
            break;
        case IO::PlayerInput::bazooka:
            this->state->bazooka(*this);
            break;
        case IO::PlayerInput::moveNone:
            break;
        case IO::PlayerInput::pointUp:
            this->state->pointUp(*this);
            break;
        case IO::PlayerInput::pointDown:
            this->state->pointDown(*this);
            break;
        case IO::PlayerInput::startShot:
            this->state->startShot(*this);
            break;
        case IO::PlayerInput::endShot:
            this->state->endShot(*this);
            break;
    }
}

void Worms::Player::setState(Worm::StateID stateID) {
    if (this->state == nullptr || this->state->getState() != stateID) {
        /* creates the right state type */
        switch (stateID) {
            case Worm::StateID::Still:
                this->state = std::shared_ptr<State>(new Still());
                break;
            case Worm::StateID::Walk:
                this->state = std::shared_ptr<State>(new Walk());
                break;
            case Worm::StateID::StartJump:
                this->state = std::shared_ptr<State>(new StartJump());
                break;
            case Worm::StateID::Jumping:
                this->state = std::shared_ptr<State>(new Jumping());
                break;
            case Worm::StateID::EndJump:
                this->state = std::shared_ptr<State>(new EndJump());
                break;
            case Worm::StateID::StartBackFlip:
                this->state = std::shared_ptr<State>(new StartBackFlip());
                break;
            case Worm::StateID::BackFlipping:
                this->state = std::shared_ptr<State>(new BackFlipping());
                break;
            case Worm::StateID::EndBackFlip:
                this->state = std::shared_ptr<State>(new EndBackFlip());
                break;
            case Worm::StateID::Hit:
                this->state = std::shared_ptr<State>(new Hit());
                break;
            case Worm::StateID::Die:
                this->state = std::shared_ptr<State>(new Die());
                break;
            case Worm::StateID::Drown:
                this->state = std::shared_ptr<State>(new Drown());
                break;
            case Worm::StateID::Dead:
                this->state = std::shared_ptr<State>(new Dead());
                this->body->SetType(b2_staticBody);
                break;
        }
    }
}

void Worms::Player::startContact() {
    this->numContacts++;
}

void Worms::Player::endContact() {
    if (this->numContacts > 0) {
        this->numContacts--;
    }
}

int Worms::Player::getContactCount() {
    return this->numContacts;
}

void Worms::Player::shoot(int shotPower) {
    Math::Point<float> position = this->getPosition();
    float safeNonContactDistance =
        sqrt((PLAYER_WIDTH / 2) * (PLAYER_WIDTH / 2) + (PLAYER_HEIGHT / 2) * (PLAYER_HEIGHT / 2));
    float angle = this->weapon.getAngle();
    if (this->direction == Direction::right) {
        if (angle < 0.0f) {
            angle += 360.0f;
        }
    } else {
        angle = 180.0f - angle;
    }
    this->bullet = std::shared_ptr<Worms::Bullet>(
        new Worms::Bullet(position, safeNonContactDistance, angle, shotPower, this->physics));
}

std::shared_ptr<Worms::Bullet> Worms::Player::getBullet() const {
    return this->bullet;
}

void Worms::Player::acknowledgeDamage(Worms::DamageInfo damageInfo, Math::Point<float> epicenter) {
    double distanceToEpicenter = this->getPosition().distance(epicenter);//std::cout << "epicenter " << epicenter.x << " "<<epicenter.y<<" position "<<this->getPosition().x <<" "<<this->getPosition().y<< std::endl;std::cout << "distance to epicenter " << distanceToEpicenter << std::endl;
    if (distanceToEpicenter <= damageInfo.radius) {
        double inflictedDamage = (1.0f - (distanceToEpicenter / (damageInfo.radius * 1.01f))) * damageInfo.damage;
        this->health -= inflictedDamage;

        Math::Point<float> positionToEpicenter = this->getPosition() - epicenter;
        float xImpactDirection = (positionToEpicenter.x > 0) - (positionToEpicenter.x < 0);
        float yImpactDirection = (positionToEpicenter.y > 0) - (positionToEpicenter.y < 0);
        float32 mass = this->body->GetMass();
        b2Vec2 impulses = {mass * float32(inflictedDamage) * xImpactDirection,
                           mass * float32(inflictedDamage) * yImpactDirection};
        b2Vec2 position = this->body->GetWorldCenter();
        this->body->ApplyLinearImpulse(impulses, position, true);
        this->setState(Worm::StateID::Hit);
        this->health = (this->health < 0) ? 0 : this->health;//std::cout << "life " << this->health << std::endl;
    }
}

void Worms::Player::destroyBullet() {
    this->bullet = nullptr;
}

float Worms::Player::getWeaponAngle() const {
    return this->weapon.getAngle();
}

const Worm::WeaponID &Worms::Player::getWeaponID() const {
    return this->weapon.getWeaponID();
}

void Worms::Player::setWeaponID(const Worm::WeaponID &id) {
    this->weapon.setWeaponID(id);
}

void Worms::Player::increaseWeaponAngle() {
    this->weapon.increaseAngle();
}

void Worms::Player::decreaseWeaponAngle() {
    this->weapon.decreaseAngle();
}

void Worms::Player::startShot() {
    this->weapon.startShot();
}

void Worms::Player::endShot() {
    this->weapon.endShot(*this);
}
