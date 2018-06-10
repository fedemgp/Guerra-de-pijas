/*
 *  Created by Rodrigo.
 *  date: 29/05/18
 */

#include "Drowning.h"
#include "Player.h"

Worms::Drowning::Drowning()
    : State(Worm::StateID::Drowning), drowningTime(Game::Config::getInstance().getDrowningTime()) {}

void Worms::Drowning::update(Worms::Player &p, float dt, b2Body *body) {
    this->timeElapsed += dt;
    if (this->timeElapsed >= this->drowningTime) {
        p.setState(Worm::StateID::Dead);
        p.notify(p, Event::Drowned);
    }
}

void Worms::Drowning::moveRight(Worms::Player &p) {}

void Worms::Drowning::moveLeft(Worms::Player &p) {}

void Worms::Drowning::jump(Worms::Player &p) {}

void Worms::Drowning::stopMove(Worms::Player &p) {}

void Worms::Drowning::backFlip(Worms::Player &p) {}

void Worms::Drowning::bazooka(Worms::Player &p) {}

void Worms::Drowning::pointUp(Worms::Player &p) {}

void Worms::Drowning::pointDown(Worms::Player &p) {}

void Worms::Drowning::startShot(Worms::Player &p) {}

void Worms::Drowning::endShot(Worms::Player &p) {}

void Worms::Drowning::grenade(Worms::Player &p) {}

void Worms::Drowning::cluster(Worms::Player &p) {}

void Worms::Drowning::mortar(Worms::Player &p) {}

void Worms::Drowning::banana(Worms::Player &p) {}

void Worms::Drowning::holy(Worms::Player &p) {}

void Worms::Drowning::setTimeout(Worms::Player &p, uint8_t time) {}
