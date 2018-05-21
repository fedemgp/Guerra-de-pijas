/*
 *  Created by Rodrigo.
 *  date: 19/05/18
 */

#include "WormJump.h"

Worm::Jump::Jump() : State(StateID::StartJump) {}

Worm::Jump::~Jump() {}

void Worm::Jump::update(float dt) {}

IO::PlayerInput Worm::Jump::moveRight(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Jump::moveLeft(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Jump::stopMove(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Jump::jump(Worm &w) {
    return IO::PlayerInput::moveNone;
}
