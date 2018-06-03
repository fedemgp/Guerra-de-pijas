/*
 *  Created by Rodrigo.
 *  date: 29/05/18
 */

#include "Drown.h"
#include "Player.h"


Worms::Drown::Drown() : State(Worm::StateID::Drown),
                        drowningTime(Game::Config::getInstance()
                                             .getDrowningTime()){}

void Worms::Drown::update(Worms::Player &p, float dt, b2Body *body) {
    this->timeElapsed += dt;
    if (this->timeElapsed >= this->drowningTime) {
        p.setState(Worm::StateID::Dead);
    }
}

void Worms::Drown::moveRight(Worms::Player &p) {}

void Worms::Drown::moveLeft(Worms::Player &p) {}

void Worms::Drown::jump(Worms::Player &p) {}

void Worms::Drown::stopMove(Worms::Player &p) {}

void Worms::Drown::backFlip(Worms::Player &p) {}

void Worms::Drown::bazooka(Worms::Player &p) {}

void Worms::Drown::pointUp(Worms::Player &p) {}

void Worms::Drown::pointDown(Worms::Player &p) {}

void Worms::Drown::startShot(Worms::Player &p) {}

void Worms::Drown::endShot(Worms::Player &p) {}

void Worms::Drown::grenade(Worms::Player &p){}
