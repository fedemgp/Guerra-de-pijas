/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */

#include <iostream>
#include <vector>

#include "Player.h"
#include "PlayerSliding.h"

Worms::Sliding::Sliding() : State(Worm::StateID::Sliding) {}

void Worms::Sliding::update(Worms::Player &p, float dt, b2Body *body) {
    if (!p.isOnGround()) {
        p.setState(Worm::StateID::Falling);
        return;
    }

    float final_vel{0.0f};

    try {
        b2Vec2 normal = p.getGroundNormal();
        float slope = std::abs(std::atan2(normal.y, normal.x));
        if ((slope < PI / 4.0f) || (slope > (PI * 3.0f) / 4.0f)) {
            final_vel = 3.0f * normal.x;
            float impulse = body->GetMass() * (final_vel - body->GetLinearVelocity().x);

            body->ApplyLinearImpulse(b2Vec2(impulse, 0.0f), body->GetWorldCenter(), true);
        } else {
            p.setState(Worm::StateID::Land);
        }
    } catch (const Exception &e) {
    }
}

void Worms::Sliding::moveRight(Worms::Player &p) {}

void Worms::Sliding::moveLeft(Worms::Player &p) {}

void Worms::Sliding::jump(Worms::Player &p) {}

void Worms::Sliding::stopMove(Worms::Player &p) {}

void Worms::Sliding::backFlip(Worms::Player &p) {}

void Worms::Sliding::bazooka(Worms::Player &p) {}

void Worms::Sliding::pointUp(Worms::Player &p) {}

void Worms::Sliding::pointDown(Worms::Player &p) {}

void Worms::Sliding::startShot(Worms::Player &p) {}

void Worms::Sliding::endShot(Worms::Player &p) {}

void Worms::Sliding::grenade(Worms::Player &p) {}

void Worms::Sliding::cluster(Worms::Player &p) {}

void Worms::Sliding::mortar(Worms::Player &p) {}

void Worms::Sliding::banana(Worms::Player &p) {}

void Worms::Sliding::holy(Worms::Player &p) {}

void Worms::Sliding::setTimeout(Worms::Player &p, uint8_t time) {}

void Worms::Sliding::aerialAttack(Worms::Player &p) {}

void Worms::Sliding::dynamite(Worms::Player &p) {}

void Worms::Sliding::teleport(Worms::Player &p) {}
