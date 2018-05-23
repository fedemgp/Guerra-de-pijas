/*
 *  Created by Rodrigo.
 *  date: 21/05/18
 */


#include "WormEndJump.h"

Worm::EndJump::EndJump() : State(StateID::EndJump) {}

Worm::EndJump::~EndJump() {}

void Worm::EndJump::update(float dt) {}

IO::PlayerInput Worm::EndJump::moveRight(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::EndJump::moveLeft(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::EndJump::stopMove(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::EndJump::jump(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::EndJump::backFlip(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::EndJump::bazooka(Worm &w){
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::EndJump::pointUp(Worm &w){
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::EndJump::pointDown(Worm &w){
    return IO::PlayerInput::moveNone;
}
