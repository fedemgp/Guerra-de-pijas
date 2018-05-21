/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */

#include "WormStateBazooka.h"

Worm::Bazooka::Bazooka(): State(StateID::Bazooka){}

Worm::Bazooka::~Bazooka(){}

void Worm::Bazooka::update(float dt){}

IO::PlayerInput Worm::Bazooka::moveRight(Worm &w){
    w.setState(StateID::Walk);
    w.direction = ::Worm::Direction::right;
    return IO::PlayerInput::moveRight;
}

IO::PlayerInput Worm::Bazooka::moveLeft(Worm &w) {
    w.setState(StateID::Walk);
    w.direction = ::Worm::Direction::left;
    return IO::PlayerInput::moveLeft;
}

IO::PlayerInput Worm::Bazooka::stopMove(Worm &w) {
    return IO::PlayerInput::stopMove;
}

IO::PlayerInput Worm::Bazooka::jump(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Bazooka::bazooka(Worm &w){
    return IO::PlayerInput::moveNone;
}
