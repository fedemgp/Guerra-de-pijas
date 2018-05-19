/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "WormWalk.h"

Worm::Walk::Walk() {}

Worm::Walk::~Walk() {}

void Worm::Walk::update(float dt) {
}

IO::PlayerInput Worm::Walk::moveLeft(Worm &w) {
    if (w.direction == Direction::left) {
        return IO::PlayerInput::moveNone;
    }

    w.direction = Direction::left;
    return IO::PlayerInput::moveLeft;
}

IO::PlayerInput Worm::Walk::moveRight(Worm &w) {
    if (w.direction == Direction::right) {
        return IO::PlayerInput::moveNone;
    }

    w.direction = Direction::right;
    return IO::PlayerInput::moveRight;
}

IO::PlayerInput Worm::Walk::stopMove(Worm &w) {
    w.setState(StateID::still);
    return IO::PlayerInput::stopMove;
}