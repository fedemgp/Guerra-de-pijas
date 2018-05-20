//
// Created by Gorco on 19/05/18.
//

#include <memory>

#include "Player.h"
#include "Player.h"
#include "PlayerStill.h"
#include "PlayerWalk.h"

float Worms::Still::update(Player &p) {
    return 0.0f;
}

void Worms::Still::moveRight(Worms::Player &p) {
    p.state = std::shared_ptr<State>(new Walk());
    p.direction = Direction::right;
}

void Worms::Still::moveLeft(Worms::Player &p) {
    p.state = std::shared_ptr<State>(new Walk());
    p.direction = Direction::left;
}

void Worms::Still::stopMove(Worms::Player &p) {}

void Worms::Still::jump(Worms::Player &p) {}

