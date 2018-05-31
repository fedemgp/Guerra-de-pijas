/*
 *  Created by Rodrigo.
 *  date: 28/05/18
 */


#include <iostream>
#include "Dead.h"

Worm::Dead::Dead() : State(StateID::Dead) {}

Worm::Dead::~Dead() {}

void Worm::Dead::update(float dt) {
//    std::cout<<"dead ";
}

IO::PlayerInput Worm::Dead::moveRight(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Dead::moveLeft(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Dead::stopMove(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Dead::jump(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Dead::backFlip(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Dead::bazooka(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Dead::pointUp(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Dead::pointDown(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Dead::startShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Dead::endShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}