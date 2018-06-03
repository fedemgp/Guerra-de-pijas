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

IO::PlayerInput Worm::Jumping::bazooka(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Jumping::pointUp(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Jumping::pointDown(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Jumping::startShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Jumping::endShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Jumping::grenade(Worm &w){
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Jumping::cluster(Worm &w){
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Jumping::mortar(Worm &w){
    return IO::PlayerInput::moveNone;
}
