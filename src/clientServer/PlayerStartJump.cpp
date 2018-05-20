//
// Created by Gorco on 19/05/18.
//

#include "PlayerStartJump.h"

Worms::StartJump::StartJump() : State(Worm::StateID::StartJump) {}

const std::vector<float> & Worms::StartJump::update(Player &p, float dt, float32 mass,
                                               const b2Vec2 &velocities) {
    this->timeElapsed += dt;
    if (this->timeElapsed >= JUMP_TIME) {
        p.setState(Worm::StateID::Jumping);
        /* When the worm jumps, it needs an initial impulse in the y axis
         * that will never will be applied again. In the x axis, the worms
         * moves in RUM, so it needs a constant impulse during all calls of
         * update.
         */
        this->impulses[0] = JUMP_IMPULSE_X;
        this->impulses[1] = JUMP_IMPULSE_Y;
    }
    return this->impulses;
}

void Worms::StartJump::moveRight(Worms::Player &p) {}

void Worms::StartJump::moveLeft(Worms::Player &p) {}

void Worms::StartJump::jump(Worms::Player &p) {}

void Worms::StartJump::stopMove(Worms::Player &p) {}
