/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */

#include "WormStateBazooka.h"

Worm::Bazooka::Bazooka(): State(StateID::Bazooka){}

Worm::Bazooka::~Bazooka(){}

void Worm::Bazooka::update(float dt){}

IO::PlayerInput Worm::Bazooka::moveRight(Worm::Worm &w){
    return IO::PlayerInput::moveRight;
}



