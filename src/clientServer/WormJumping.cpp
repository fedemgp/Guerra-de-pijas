/*
 *  Created by Rodrigo.
 *  date: 21/05/18
 */


#include "WormJumping.h"

Worm::Jumping::Jumping() : State(StateID::Jumping) {}

Worm::Jumping::~Jumping() {}

void Worm::Jumping::update(float dt) {}

IO::PlayerInput Worm::Jumping::moveRight(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Jumping::moveLeft(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Jumping::stopMove(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Jumping::jump(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Jumping::backFlip(Worm &w) {
    return IO::PlayerInput::moveNone;
}
