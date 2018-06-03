/*
 *  Created by Rodrigo.
 *  date: 28/05/18
 */

#include "Die.h"

Worm::Die::Die() : State(StateID::Die) {}

Worm::Die::~Die() {}

void Worm::Die::update(float dt) {}

IO::PlayerInput Worm::Die::moveRight(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Die::moveLeft(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Die::stopMove(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Die::jump(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Die::backFlip(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Die::bazooka(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Die::pointUp(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Die::pointDown(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Die::startShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Die::endShot(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Die::grenade(Worm &w){
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Die::cluster(Worm &w){
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Die::mortar(Worm &w){
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::Die::banana(Worm &w){
    return IO::PlayerInput::moveNone;
}
