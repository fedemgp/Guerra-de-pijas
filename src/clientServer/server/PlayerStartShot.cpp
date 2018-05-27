//
// Created by rodrigo on 24/05/18.
//

#include "PlayerStartShot.h"

Worms::StartShot::StartShot() : State(Worm::StateID::StartShot) {}

void Worms::StartShot::update(Player &p, float dt, b2Body *body){

}

void Worms::StartShot::moveRight(Worms::Player &p) {}

void Worms::StartShot::moveLeft(Worms::Player &p) {}

void Worms::StartShot::stopMove(Worms::Player &p) {}

void Worms::StartShot::jump(Worms::Player &p) {}

void Worms::StartShot::backFlip(Worms::Player &p) {}

void Worms::StartShot::bazooka(Worms::Player &p) {}

void Worms::StartShot::pointUp(Worms::Player &p){}

void Worms::StartShot::pointDown(Worms::Player &p) {}

void Worms::StartShot::startShot(Worms::Player &p) {}
