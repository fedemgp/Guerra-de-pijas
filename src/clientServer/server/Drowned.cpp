//
// Created by rodrigo on 9/06/18.
//

#include "Drowned.h"
#include "Player.h"

Worms::Drowned::Drowned()
        : State(Worm::StateID::Drowned) {}

void Worms::Drowned::update(Worms::Player &p, float dt, b2Body *body) {}

void Worms::Drowned::moveRight(Worms::Player &p) {}

void Worms::Drowned::moveLeft(Worms::Player &p) {}

void Worms::Drowned::jump(Worms::Player &p) {}

void Worms::Drowned::stopMove(Worms::Player &p) {}

void Worms::Drowned::backFlip(Worms::Player &p) {}

void Worms::Drowned::bazooka(Worms::Player &p) {}

void Worms::Drowned::pointUp(Worms::Player &p) {}

void Worms::Drowned::pointDown(Worms::Player &p) {}

void Worms::Drowned::startShot(Worms::Player &p) {}

void Worms::Drowned::endShot(Worms::Player &p) {}

void Worms::Drowned::grenade(Worms::Player &p) {}

void Worms::Drowned::cluster(Worms::Player &p) {}

void Worms::Drowned::mortar(Worms::Player &p) {}

void Worms::Drowned::banana(Worms::Player &p) {}

void Worms::Drowned::holy(Worms::Player &p) {}

void Worms::Drowned::setTimeout(Worms::Player &p, uint8_t time) {}
