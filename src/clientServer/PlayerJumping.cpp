/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */

#include "PlayerJumping.h"

Worms::Jumping::Jumping(): State(Worm::StateID::Jumping){}

const std::vector<float> &
Worms::Jumping::update(Worms::Player &p, float dt, float32 mass,
                       const b2Vec2 &velocities){
    return this->impulses;
}

void Worms::Jumping::moveRight(Worms::Player &p){}

void Worms::Jumping::moveLeft(Worms::Player &p){}

void Worms::Jumping::jump(Worms::Player &p){}

void Worms::Jumping::stopMove(Worms::Player &p){}
