/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <Box2D/Box2D.h>

#include "Physics.h"
#include "Player.h"
#include "PlayerStartJump.h"
#include "PlayerStill.h"
#include "PlayerWalk.h"
#include "PlayerJumping.h"
#include "PlayerEndJump.h"
#include "PlayerBazooka.h"

Worms::Player::Player(Physics &physics, bool active): active(active) {
    this->bodyDef.type = b2_dynamicBody;
    this->bodyDef.position.Set(0.0f, 0.0f);
    this->bodyDef.fixedRotation = true;

    this->body = physics.createBody(this->bodyDef);
    const float width = 0.8f;
    const float height = 2.0f;
    this->shape.SetAsBox(width / 2, height / 2);
    this->fixture.shape = &this->shape;
    this->fixture.density = 1.0f;
    this->fixture.restitution = 0.1f;
    this->fixture.friction = 0.0f;

    this->body->CreateFixture(&this->fixture);
    this->body->SetUserData(this);

    this->state = std::shared_ptr<State>(new Still());
    this->direction = Direction::left;
}

void Worms::Player::update(float dt) {
    this->state->update(*this, dt, this->body);
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
            case Worm::StateID::Bazooka:
                this->state = std::shared_ptr<State>(new Bazooka());
                break;
        }
    }
}

void Worms::Player::startContact(){
    this->state->startContact();
}

void Worms::Player::endContact(){
    this->state->endContact();
}

void Worms::Player::increaseAngle(){
    this->angle += ANGLE_STEP;
    if (this->angle > MAX_ANGLE){
        this->angle = MAX_ANGLE;
    }
}

void Worms::Player::decreaseAngle(){
    this->angle -= ANGLE_STEP;
    if (this->angle < MIN_ANGLE){
        this->angle = MIN_ANGLE;
    }
}

bool Worms::Player::isActive() const{
    return this->active;
}

float Worms::Player::getAngle() const{
    return this->angle;
}

