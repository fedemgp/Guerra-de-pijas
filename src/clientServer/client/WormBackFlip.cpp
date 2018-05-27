/*
 *  Created by Rodrigo.
 *  date: 20/05/18
 */


#include "WormBackFlip.h"

Worm::BackFlip::BackFlip() : State(StateID::StartBackFlip) {}

Worm::BackFlip::~BackFlip() {}

void Worm::BackFlip::update(float dt) {}

IO::PlayerInput Worm::BackFlip::moveRight(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlip::moveLeft(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlip::stopMove(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlip::jump(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlip::backFlip(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlip::bazooka(Worm &w){
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlip::pointUp(Worm &w){
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlip::pointDown(Worm &w){
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlip::startShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlip::endShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}
