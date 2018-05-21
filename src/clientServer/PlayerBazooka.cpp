//
// Created by rodrigo on 21/05/18.
//

#include "PlayerBazooka.h"
#include "Player.h"

Worms::Bazooka::Bazooka() : State(Worm::StateID::Bazooka) {}

void Worms::Bazooka::update(Worms::Player &p, float dt, b2Body *body){

}

void Worms::Bazooka::moveRight(Worms::Player &p) {}

void Worms::Bazooka::moveLeft(Worms::Player &p) {}

void Worms::Bazooka::jump(Worms::Player &p) {}

void Worms::Bazooka::stopMove(Worms::Player &p) {}

void Worms::Bazooka::bazooka(Worms::Player &p) {}
