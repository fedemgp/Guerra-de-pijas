/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <Box2D/Box2D.h>

#include "Physics.h"
#include "Player.h"
#include "PlayerBackFlipping.h"
#include "PlayerBazooka.h"
#include "PlayerEndBackFlip.h"
#include "PlayerEndJump.h"
#include "PlayerJumping.h"
#include "PlayerStartBackFlip.h"
#include "PlayerStartJump.h"
#include "PlayerStill.h"
#include "PlayerWalk.h"

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
    if (this->bullet != nullptr) {
        this->bullet->update(dt);
        if (this->bullet->madeImpact()) {
            this->bullet = nullptr;
        }
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
            case Worm::StateID::Bazooka:
                this->state = std::shared_ptr<State>(new Bazooka());
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

void Worms::Player::increaseAngle() {
    this->angle += ANGLE_STEP;
    if (this->angle > MAX_ANGLE) {
        this->angle = MAX_ANGLE;
    }
}

void Worms::Player::decreaseAngle() {
    this->angle -= ANGLE_STEP;
    if (this->angle < MIN_ANGLE) {
        this->angle = MIN_ANGLE;
    }
}

float Worms::Player::getAngle() const {
    return this->angle;
}

int Worms::Player::getContactCount() {
    return this->numContacts;
}

void Worms::Player::shoot(int shotPower) {
    Math::Point<float> position = this->getPosition();
    float safeNonContactDistance =
        sqrt((PLAYER_WIDTH / 2) * (PLAYER_WIDTH / 2) + (PLAYER_HEIGHT / 2) * (PLAYER_HEIGHT / 2));
    float angle = this->getAngle();
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

Worm::WeaponID Worms::Player::getWeaponID() const{
    return this->weapon.getWeaponID();
}

void Worms::Player::setWeaponID(const Worm::WeaponID &id){
    this->weapon.setWeaponID(id);
}
