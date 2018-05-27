/*
 *  Created by Rodrigo.
 *  date: 21/05/18
 */


#include "WormBackFlipping.h"

Worm::BackFlipping::BackFlipping() : State(StateID::BackFlipping) {}

Worm::BackFlipping::~BackFlipping() {}

void Worm::BackFlipping::update(float dt) {}

IO::PlayerInput Worm::BackFlipping::moveRight(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::moveLeft(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::stopMove(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::jump(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::backFlip(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::bazooka(Worm &w){
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::pointUp(Worm &w){
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::pointDown(Worm &w){
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::startShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}
