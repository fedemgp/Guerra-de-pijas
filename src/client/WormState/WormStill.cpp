/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "WormStill.h"
#include <iostream>
#include "Texture.h"

Worm::Still::Still() : State(StateID::Still) {}

Worm::Still::~Still() {}

void Worm::Still::update(float dt) {}

IO::PlayerInput Worm::Still::moveRight(Worm &w) {
    return IO::PlayerInput::moveRight;
}

IO::PlayerInput Worm::Still::moveLeft(Worm &w) {
    return IO::PlayerInput::moveLeft;
}

IO::PlayerInput Worm::Still::stopMove(Worm &w) {
    return IO::PlayerInput::stopMove;
}

IO::PlayerInput Worm::Still::jump(Worm &w) {
    return IO::PlayerInput::startJump;
}

IO::PlayerInput Worm::Still::backFlip(Worm &w) {
    return IO::PlayerInput::startBackFlip;
}

IO::PlayerInput Worm::Still::bazooka(Worm &w) {
    return IO::PlayerInput::bazooka;
}

IO::PlayerInput Worm::Still::pointUp(Worm &w) {
    return IO::PlayerInput::pointUp;
}

IO::PlayerInput Worm::Still::pointDown(Worm &w) {
    return IO::PlayerInput::pointDown;
}

IO::PlayerInput Worm::Still::startShot(Worm &w) {
    w.startShot();
    return IO::PlayerInput::startShot;
}

IO::PlayerInput Worm::Still::endShot(Worm &w) {
    w.endShot();
    return IO::PlayerInput::endShot;
}

IO::PlayerInput Worm::Still::grenade(Worm &w) {
    return IO::PlayerInput::grenade;
}

IO::PlayerInput Worm::Still::cluster(Worm &w) {
    return IO::PlayerInput::cluster;
}

IO::PlayerInput Worm::Still::mortar(Worm &w) {
    return IO::PlayerInput::mortar;
}

IO::PlayerInput Worm::Still::banana(Worm &w) {
    return IO::PlayerInput::banana;
}

IO::PlayerInput Worm::Still::holy(Worm &w) {
    return IO::PlayerInput::holy;
}

IO::PlayerInput Worm::Still::setTimeoutTo(Worm &w, int time) {
    switch (time) {
        case 1:
            return IO::PlayerInput::timeout1;
        case 2:
            return IO::PlayerInput::timeout2;
        case 3:
            return IO::PlayerInput::timeout3;
        case 4:
            return IO::PlayerInput::timeout4;
        case 5:
            return IO::PlayerInput::timeout5;
        default:
            return IO::PlayerInput::moveNone;
    }
}

IO::PlayerInput Worm::Still::aerialAttack(Worm &w) {
    return IO::PlayerInput::aerialAttack;
}

IO::PlayerInput Worm::Still::positionSelected(Worm &w) {
    return IO::PlayerInput::positionSelected;
}

IO::PlayerInput Worm::Still::dynamite(Worm &w) {
    return IO::PlayerInput::dynamite;
}

IO::PlayerInput Worm::Still::teleport(Worm &w) {
    return IO::PlayerInput::teleport;
}

IO::PlayerInput Worm::Still::baseballBat(Worm &w) {
    return IO::PlayerInput::baseballBat;
}
