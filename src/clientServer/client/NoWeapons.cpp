//
// Created by rodrigo on 28/05/18.
//

#include "NoWeapons.h"
#include "Texture.h"

Worm::NoWeapons::NoWeapons() : State(StateID::NoWeapons) {}

Worm::NoWeapons::~NoWeapons() {}

void Worm::NoWeapons::update(float dt) {}

IO::PlayerInput Worm::NoWeapons::moveRight(Worm &w) {
    w.setState(StateID::Walk);
    w.direction = ::Worm::Direction::right;
    return IO::PlayerInput::moveRight;
}

IO::PlayerInput Worm::NoWeapons::moveLeft(Worm &w) {
    w.setState(StateID::Walk);
    w.direction = ::Worm::Direction::left;
    return IO::PlayerInput::moveLeft;
}

IO::PlayerInput Worm::NoWeapons::stopMove(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::NoWeapons::jump(Worm &w) {
    w.setState(StateID::StartJump);
    return IO::PlayerInput::startJump;
}

IO::PlayerInput Worm::NoWeapons::backFlip(Worm &w) {
    w.setState(StateID::StartBackFlip);
    return IO::PlayerInput::startBackFlip;
}

IO::PlayerInput Worm::NoWeapons::bazooka(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::NoWeapons::pointUp(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::NoWeapons::pointDown(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::NoWeapons::startShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::NoWeapons::endShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}
