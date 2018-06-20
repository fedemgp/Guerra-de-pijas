/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "WormWalk.h"

Worm::Walk::Walk() : State(StateID::Walk) {}

Worm::Walk::~Walk() {}

void Worm::Walk::update(float dt) {}

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
    w.setState(StateID::Still);
    return IO::PlayerInput::stopMove;
}

IO::PlayerInput Worm::Walk::jump(Worm &w) {
    w.setState(StateID::StartJump);
    return IO::PlayerInput::startJump;
}

IO::PlayerInput Worm::Walk::backFlip(Worm &w) {
    w.setState(StateID::StartBackFlip);
    return IO::PlayerInput::startBackFlip;
}

IO::PlayerInput Worm::Walk::bazooka(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Walk::pointUp(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Walk::pointDown(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Walk::startShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Walk::endShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Walk::grenade(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Walk::cluster(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Walk::mortar(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Walk::banana(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Walk::holy(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Walk::setTimeoutTo(Worm &w, int t) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Walk::aerialAttack(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Walk::positionSelected(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Walk::dynamite(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Walk::teleport(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Walk::baseballBat(Worm &w) {
    return IO::PlayerInput::moveNone;
}
