/*
 *  Created by Rodrigo.
 *  date: 29/05/18
 */

#include "Drown.h"

Worm::Drown::Drown() : State(StateID::Drown) {}

Worm::Drown::~Drown() {}

void Worm::Drown::update(float dt) {}

IO::PlayerInput Worm::Drown::moveRight(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Drown::moveLeft(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Drown::stopMove(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Drown::jump(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Drown::backFlip(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Drown::bazooka(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Drown::pointUp(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Drown::pointDown(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Drown::startShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Drown::endShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}