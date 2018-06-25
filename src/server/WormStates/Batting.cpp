//
// Created by rodrigo on 23/06/18.
//

#include "Batting.h"
#include "../Config/Config.h"
#include "../Player.h"

Worms::Batting::Batting()
    : State(Worm::StateID::Batting), battingTime(Game::Config::getInstance().getBattingTime()) {}

void Worms::Batting::update(Worms::Player &p, float dt, b2Body *body) {
    this->timeElapsed += dt;
    if (this->timeElapsed >= this->battingTime) {
        p.setState(Worm::StateID::Still);
    }
}

void Worms::Batting::moveRight(Worms::Player &p) {}

void Worms::Batting::moveLeft(Worms::Player &p) {}

void Worms::Batting::jump(Worms::Player &p) {}

void Worms::Batting::stopMove(Worms::Player &p) {}

void Worms::Batting::backFlip(Worms::Player &p) {}

void Worms::Batting::bazooka(Worms::Player &p) {}

void Worms::Batting::pointUp(Worms::Player &p) {}

void Worms::Batting::pointDown(Worms::Player &p) {}

void Worms::Batting::startShot(Worms::Player &p) {}

void Worms::Batting::endShot(Worms::Player &p) {}

void Worms::Batting::grenade(Worms::Player &p) {}

void Worms::Batting::cluster(Worms::Player &p) {}

void Worms::Batting::mortar(Worms::Player &p) {}

void Worms::Batting::banana(Worms::Player &p) {}

void Worms::Batting::holy(Worms::Player &p) {}

void Worms::Batting::setTimeout(Worms::Player &p, uint8_t time) {}

void Worms::Batting::aerialAttack(Worms::Player &p) {}

void Worms::Batting::dynamite(Worms::Player &p) {}

void Worms::Batting::teleport(Worms::Player &p) {}

void Worms::Batting::baseballBat(Worms::Player &p) {}
