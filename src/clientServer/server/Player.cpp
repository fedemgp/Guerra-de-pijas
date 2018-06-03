/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <Box2D/Box2D.h>
#include <iostream>

#include "Bazooka.h"
#include "Dead.h"
#include "Die.h"
#include "Drown.h"
#include "Grenade.h"
#include "Hit.h"
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
#include "Weapon.h"
#include "Cluster.h"
#include "Mortar.h"
#include "Banana.h"
#include "Holy.h"

Worms::Player::Player(Physics &physics)
    : PhysicsEntity(Worms::EntityID::EtWorm),
      physics(physics),
      waterLevel(Game::Config::getInstance().getWaterLevel()) {
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
    this->weapon = std::shared_ptr<Worms::Weapon>(new ::Weapon::Bazooka(0.0f));
}

void Worms::Player::update(float dt) {
    this->state->update(*this, dt, this->body);
    this->weapon->update(dt);

    if (this->getPosition().y <= this->waterLevel && this->numContacts == 0 &&
        this->getStateId() != Worm::StateID::Dead && this->getStateId() != Worm::StateID::Drown) {
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
        case IO::PlayerInput::grenade:
            this->state->grenade(*this);
            break;
        case IO::PlayerInput::cluster:
            this->state->cluster(*this);
            break;
        case IO::PlayerInput::mortar:
            this->state->mortar(*this);
            break;
        case IO::PlayerInput::banana:
            this->state->banana(*this);
            break;
        case IO::PlayerInput::holy:
            this->state->holy(*this);
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

std::shared_ptr<Worms::Bullet> Worms::Player::getBullet() const {
    return this->weapon->getBullet();
}

void Worms::Player::acknowledgeDamage(Worms::DamageInfo damageInfo, Math::Point<float> epicenter) {
    if (this->getStateId() != Worm::StateID::Dead) {
        double distanceToEpicenter = this->getPosition().distance(
            epicenter);  // std::cout << "epicenter " << epicenter.x << " "<<epicenter.y<<" position
        // "<<this->getPosition().x <<" "<<this->getPosition().y<< std::endl;std::cout
        // << "distance to epicenter " << distanceToEpicenter << std::endl;
        if (distanceToEpicenter <= damageInfo.radius) {
            double inflictedDamage =
                (1.0f - (distanceToEpicenter / (damageInfo.radius * 1.01f))) * damageInfo.damage;
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
            this->health =
                (this->health < 0)
                    ? 0
                    : this->health;  // std::cout << "life " << this->health << std::endl;
        }
    }
}

void Worms::Player::destroyBullet() {
    this->weapon->destroyBullet();
}

float Worms::Player::getWeaponAngle() const {
    return this->weapon->getAngle();
}

const Worm::WeaponID &Worms::Player::getWeaponID() const {
    return this->weapon->getWeaponID();
}
// TODO add creation time in Team, and in this method ask for it. So that the
// team tracks weapons quantity
void Worms::Player::setWeapon(const Worm::WeaponID &id){
    if (this->weapon->getWeaponID() != id){
        //keep the last angle
        float lastAngle = this->weapon->getAngle();
        switch (id){
            case Worm::WeaponID::WBazooka:
                this->weapon = std::shared_ptr<Worms::Weapon>(
                        new ::Weapon::Bazooka(lastAngle));
                break;
            case Worm::WeaponID::WGrenade:
                this->weapon = std::shared_ptr<Worms::Weapon>(
                        new ::Weapon::Grenade(lastAngle));
                break;
            case Worm::WeaponID::WCluster:
                this->weapon = std::shared_ptr<Worms::Weapon>(
                        new ::Weapon::Cluster(lastAngle));
                break;
            case Worm::WeaponID::WMortar:
                this->weapon = std::shared_ptr<Worms::Weapon>(
                        new ::Weapon::Mortar(lastAngle));
                break;
            case Worm::WeaponID::WBanana:
                this->weapon = std::shared_ptr<Worms::Weapon>(
                        new ::Weapon::Banana(lastAngle));
                break;
            case Worm::WeaponID::WHoly:
                this->weapon = std::shared_ptr<Worms::Weapon>(
                        new ::Weapon::Holy(lastAngle));
                break;
            case Worm::WeaponID::WNone:
                break;
        }
    }
}

    void Worms::Player::increaseWeaponAngle() {
        this->weapon->increaseAngle();
    }

    void Worms::Player::decreaseWeaponAngle() {
        this->weapon->decreaseAngle();
    }

    void Worms::Player::startShot() {
        this->weapon->startShot();
    }

    void Worms::Player::endShot() {
        this->weapon->endShot(*this, this->physics);
    }

    void Worms::Player::setTeam(uint8_t team) {
        this->team = team;
    }

    void Worms::Player::increaseHealth(float percentage) {
        this->health += (percentage / 100.0f) * this->health;
    }

    uint8_t Worms::Player::getTeam() const {
        return this->team;
    }

    void Worms::Player::setId(uint8_t id) {
        this->id = id;
    }

    uint8_t Worms::Player::getId() const {
        return this->id;
    }
