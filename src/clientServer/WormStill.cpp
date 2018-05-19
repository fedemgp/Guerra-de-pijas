/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "WormStill.h"
#include "Texture.h"

Worm::Still::Still() {}

Worm::Still::~Still() {}

void Worm::Still::update(float dt) {
}

IO::PlayerInput Worm::Still::moveRight(Worm &w) {
    w.setState(::Worm::StateID::walk);
    w.direction = ::Worm::Direction::right;
    return IO::PlayerInput::moveRight;
}

IO::PlayerInput Worm::Still::moveLeft(Worm &w) {
    w.setState(::Worm::StateID::walk);
    w.direction = ::Worm::Direction::left;
    return IO::PlayerInput::moveLeft;
}

IO::PlayerInput Worm::Still::stopMove(Worm &w) {
    return IO::PlayerInput::moveNone;
}
