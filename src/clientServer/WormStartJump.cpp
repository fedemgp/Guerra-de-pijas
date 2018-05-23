/*
 *  Created by Rodrigo.
 *  date: 19/05/18
 */

#include "WormStartJump.h"

Worm::StartJump::StartJump() : State(StateID::StartJump) {}

Worm::StartJump::~StartJump() {}

void Worm::StartJump::update(float dt) {}

IO::PlayerInput Worm::StartJump::moveRight(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::StartJump::moveLeft(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::StartJump::stopMove(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::StartJump::jump(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::StartJump::backFlip(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::StartJump::bazooka(Worm &w){
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::StartJump::pointUp(Worm &w){
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::StartJump::pointDown(Worm &w){
    return IO::PlayerInput::moveNone;
}
