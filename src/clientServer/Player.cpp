/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <Box2D/Box2D.h>

#include "Physics.h"
#include "Player.h"
#include "PlayerStill.h"

Worms::Player::Player(Physics &physics) {
    this->bodyDef.type = b2_dynamicBody;
    this->bodyDef.position.Set(0.0f, 0.0f);

    this->body = physics.createBody(this->bodyDef);

    this->shape.SetAsBox(1.0f, 2.0f);
    this->fixture.shape = &this->shape;
    this->fixture.density = 1.0f;
    this->fixture.restitution = 0.3f;
    this->fixture.friction = 0.0f;

    this->body->CreateFixture(&this->fixture);

    this->state = std::shared_ptr<State>(new Still());
}

void Worms::Player::update(float dt) {
    float final_vel = this->state->update();

    b2Vec2 vel = this->body->GetLinearVelocity();
    const float delta = final_vel - vel.x;
    float impulse = this->body->GetMass() * delta;
    this->body->ApplyLinearImpulse(b2Vec2(impulse, 0), this->body->GetWorldCenter(), true);
}

void Worms::Player::setPosition(const Math::Point<float> &new_pos) {
    this->body->SetTransform(b2Vec2(new_pos.x, new_pos.y), body->GetAngle());
}

Math::Point<float> Worms::Player::getPosition() const {
    const b2Vec2 &pos = this->body->GetPosition();
    return Math::Point<float>{pos.x, pos.y};
}

void Worms::Player::handleState(IO::PlayerInput pi) {
    switch (pi) {
        case IO::PlayerInput::moveLeft:
            this->state->moveLeft(*this);
            break;
        case IO::PlayerInput::moveRight:
            this->state->moveRight(*this);
            break;
        case IO::PlayerInput::stopMove:
            this->state->stopMove(*this);
            break;
        case IO::PlayerInput::moveNone:
            break;
    }
}
