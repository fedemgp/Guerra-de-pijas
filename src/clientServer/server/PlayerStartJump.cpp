//
// Created by Gorco on 19/05/18.
//

#include "PlayerStartJump.h"
#include "Config.h"
#include <iostream>

Worms::StartJump::StartJump() : State(Worm::StateID::StartJump),
                                jumpTime(Game::Config::getInstance()
                                                      .getStartJumpTime()),
                                jumpVelocity(Game::Config::getInstance()
                                                     .getJumpVelocity()){}

void Worms::StartJump::update(Player &p, float dt, b2Body *body) {
    this->timeElapsed += dt;
    if (this->timeElapsed >= this->jumpTime) {
        if (!this->impulseApplied) {
            float32 mass = body->GetMass();
            b2Vec2 impulses = {mass * this->jumpVelocity.x,
                               mass * this->jumpVelocity.y};
            if (p.direction == Direction::left) {
                impulses.x *= -1;
            }
            /* When the worm jumps, it needs an initial impulse in the y axis
             * that will never will be applied again. In the x axis, the worms
             * moves in RUM, so it needs an initial impulse (because his friction
             * coeficient is 0) and then needs an end impulse, of equal absolute
             * value and different sign.
             */
            body->ApplyLinearImpulse(impulses, body->GetWorldCenter(), true);
            this->impulseApplied = true;
        } else if (p.getContactCount() == 0) {
            p.setState(Worm::StateID::Jumping);
        }
    }
}

void Worms::StartJump::moveRight(Worms::Player &p) {}

void Worms::StartJump::moveLeft(Worms::Player &p) {}

void Worms::StartJump::jump(Worms::Player &p) {}

void Worms::StartJump::stopMove(Worms::Player &p) {}

void Worms::StartJump::backFlip(Worms::Player &p) {}

void Worms::StartJump::bazooka(Worms::Player &p) {}

void Worms::StartJump::pointUp(Worms::Player &p) {}

void Worms::StartJump::pointDown(Worms::Player &p) {}

void Worms::StartJump::startShot(Worms::Player &p) {}

void Worms::StartJump::endShot(Worms::Player &p) {}

void Worms::StartJump::grenade(Worms::Player &p){}

void Worms::StartJump::cluster(Worms::Player &p){}

void Worms::StartJump::mortar(Worms::Player &p){}

void Worms::StartJump::banana(Worms::Player &p){}

void Worms::StartJump::holy(Worms::Player &p){}
