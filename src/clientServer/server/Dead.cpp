/*
 *  Created by Rodrigo.
 *  date: 28/05/18
 */


#include "Dead.h"
#include "Player.h"

Worms::Dead::Dead() : State(Worm::StateID::Dead) {}

void Worms::Dead::update(Worms::Player &p, float dt, b2Body *body) {}

void Worms::Dead::moveRight(Worms::Player &p) {}

void Worms::Dead::moveLeft(Worms::Player &p) {}

void Worms::Dead::jump(Worms::Player &p) {}

void Worms::Dead::stopMove(Worms::Player &p) {}

void Worms::Dead::backFlip(Worms::Player &p) {}

void Worms::Dead::bazooka(Worms::Player &p) {}

void Worms::Dead::pointUp(Worms::Player &p) {}

void Worms::Dead::pointDown(Worms::Player &p) {}

void Worms::Dead::startShot(Worms::Player &p) {}

void Worms::Dead::endShot(Worms::Player &p) {}