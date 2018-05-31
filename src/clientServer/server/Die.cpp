/*
 *  Created by Rodrigo.
 *  date: 28/05/18
 */

#include "Die.h"
#include "Player.h"

#define DYING_TIME 2.6f

Worms::Die::Die() : State(Worm::StateID::Die) {}

void Worms::Die::update(Worms::Player &p, float dt, b2Body *body) {
    this->timeElapsed += dt;
    if (this->timeElapsed >= DYING_TIME) {
        p.setState(Worm::StateID::Dead);
    }
}

void Worms::Die::moveRight(Worms::Player &p) {}

void Worms::Die::moveLeft(Worms::Player &p) {}

void Worms::Die::jump(Worms::Player &p) {}

void Worms::Die::stopMove(Worms::Player &p) {}

void Worms::Die::backFlip(Worms::Player &p) {}

void Worms::Die::bazooka(Worms::Player &p) {}

void Worms::Die::pointUp(Worms::Player &p) {}

void Worms::Die::pointDown(Worms::Player &p) {}

void Worms::Die::startShot(Worms::Player &p) {}

void Worms::Die::endShot(Worms::Player &p) {}
