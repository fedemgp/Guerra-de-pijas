/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <Box2D/Box2D.h>
#include <iostream>

#include "Physics.h"
#include "Player.h"
#include "PlayerStartJump.h"
#include "PlayerStill.h"
#include "PlayerWalk.h"
#include "PlayerJumping.h"

Worms::Player::Player(Physics &physics) {
    this->bodyDef.type = b2_dynamicBody;
    this->bodyDef.position.Set(0.0f, 0.0f);
    this->bodyDef.fixedRotation = true;

    this->body = physics.createBody(this->bodyDef);
    const float width = 0.8f;
    const float height = 2.0f;
    this->shape.SetAsBox(width / 2, height / 2);
    this->fixture.shape = &this->shape;
    this->fixture.density = 1.0f;
    this->fixture.restitution = 0.3f;
    this->fixture.friction = 0.0f;

    this->body->CreateFixture(&this->fixture);

    this->state = std::shared_ptr<State>(new Still());
    this->direction = Direction::left;
}

void Worms::Player::update(float dt) {
    const std::vector<float> &impulses =
        this->state->update(*this, dt, this->body->GetMass(), this->body->GetLinearVelocity());

//    b2Vec2 vel = this->body->GetLinearVelocity();
//        const float delta = impulses[0] - vel.x;
//        float impulse = this->body->GetMass() * delta;
//
    std::cout << "impulses = [" << impulses[0] << ',' << impulses[1] << std::endl;
    this->body->ApplyLinearImpulse(b2Vec2(impulses[0], impulses[1]),
                                   this->body->GetWorldCenter(), true);
//    std::cout << this->body->GetPosition().x << ", " << this->body->GetPosition().y << std::endl;
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
        case IO::PlayerInput::moveNone:
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
        }
    }
}
