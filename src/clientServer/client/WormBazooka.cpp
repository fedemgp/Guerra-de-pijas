/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */

#include "WormBazooka.h"

Worm::Bazooka::Bazooka(): State(StateID::Bazooka){}

Worm::Bazooka::~Bazooka(){}

void Worm::Bazooka::update(float dt){}

IO::PlayerInput Worm::Bazooka::moveRight(Worm &w){
    if (w.direction != Direction::right){
        w.direction = ::Worm::Direction::right;
        return IO::PlayerInput::moveNone;
    } else{
        w.setState(StateID::Walk);
        return IO::PlayerInput::moveRight;
    }
}

IO::PlayerInput Worm::Bazooka::moveLeft(Worm &w) {
    if (w.direction != Direction::left){
        w.direction = ::Worm::Direction::left;
        return IO::PlayerInput::moveNone;
    } else{
        w.setState(StateID::Walk);
        return IO::PlayerInput::moveLeft;
    }
}

IO::PlayerInput Worm::Bazooka::stopMove(Worm &w) {
    return IO::PlayerInput::stopMove;
}

IO::PlayerInput Worm::Bazooka::jump(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Bazooka::backFlip(Worm &w) {
    w.setState(StateID::StartBackFlip);
    return IO::PlayerInput::startBackFlip;
}

IO::PlayerInput Worm::Bazooka::bazooka(Worm &w){
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Bazooka::pointUp(Worm &w){
    return IO::PlayerInput::pointUp;
}

IO::PlayerInput Worm::Bazooka::pointDown(Worm &w){
    return IO::PlayerInput::pointDown;
}

IO::PlayerInput Worm::Bazooka::startShot(Worm::Worm &w) {
    return IO::PlayerInput::startShot;
}
