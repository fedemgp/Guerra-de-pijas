//
// Created by Gorco on 19/05/18.
//

#include <memory>
#include <iostream>

#include "Player.h"
#include "Player.h"
#include "PlayerStill.h"
#include "PlayerWalk.h"

Worms::Still::Still() : State(Worm::StateID::Still) {}

const std::vector<float> & Worms::Still::update(Player &p, float dt, float32 mass,
                                                const b2Vec2 &velocities) {
    this->impulses[0] = -velocities.x * mass;
    return this->impulses;
}

void Worms::Still::moveRight(Worms::Player &p) {
    p.setState(Worm::StateID::Walk);
    p.direction = Direction::right;
}

void Worms::Still::moveLeft(Worms::Player &p) {
    p.setState(Worm::StateID::Walk);
    p.direction = Direction::left;
}

void Worms::Still::stopMove(Worms::Player &p) {}

void Worms::Still::jump(Worms::Player &p) {
    p.setState(Worm::StateID::StartJump);
}
