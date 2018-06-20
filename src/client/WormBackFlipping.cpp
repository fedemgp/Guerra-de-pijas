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

IO::PlayerInput Worm::BackFlipping::bazooka(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::pointUp(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::pointDown(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::startShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::endShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::grenade(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::cluster(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::mortar(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::banana(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::holy(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::setTimeoutTo(Worm &w, int t) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::aerialAttack(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::positionSelected(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::dynamite(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::teleport(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::BackFlipping::baseballBat(Worm &w) {
    return IO::PlayerInput::moveNone;
}
