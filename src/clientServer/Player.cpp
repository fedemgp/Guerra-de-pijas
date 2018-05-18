/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <Box2D/Box2D.h>

#include "Physics.h"
#include "Player.h"

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
}

void Worms::Player::update(float dt) {
    float final_vel = 0.0f;
    switch (this->state) {
        case PlayerState::still:
            final_vel = 0.0f;
            break;
        case PlayerState::movingLeft:
            final_vel = -3.0f;
            break;
        case PlayerState::movingRight:
            final_vel = 3.0f;
            break;
    }

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

void Worms::Player::moveRight() {
    this->state = PlayerState::movingRight;
}

void Worms::Player::moveLeft() {
    this->state = PlayerState::movingLeft;
}

void Worms::Player::stopMove() {
    this->state = PlayerState::still;
}