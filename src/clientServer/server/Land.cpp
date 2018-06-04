//
// Created by rodrigo on 3/06/18.
//

#include "Land.h"
#include "Player.h"
#include "Config.h"
#include "PlayerState.h"

Worms::Land::Land()
        : State(Worm::StateID::Land),
          landTime(Game::Config::getInstance().getLandTime()) {}

void Worms::Land::update(Worms::Player &p, float dt, b2Body *body) {
    this->timeElapsed += dt;
    if (this->timeElapsed > this->landTime) {
        p.setState(Worm::StateID::Still);
    }
}

void Worms::Land::moveRight(Worms::Player &p) {}

void Worms::Land::moveLeft(Worms::Player &p) {}

void Worms::Land::jump(Worms::Player &p) {}

void Worms::Land::stopMove(Worms::Player &p) {}

void Worms::Land::backFlip(Worms::Player &p) {}

void Worms::Land::bazooka(Worms::Player &p) {}

void Worms::Land::pointUp(Worms::Player &p) {}

void Worms::Land::pointDown(Worms::Player &p) {}

void Worms::Land::startShot(Worms::Player &p) {}

void Worms::Land::endShot(Worms::Player &p) {}

void Worms::Land::grenade(Worms::Player &p) {}

void Worms::Land::cluster(Worms::Player &p) {}

void Worms::Land::mortar(Worms::Player &p) {}

void Worms::Land::banana(Worms::Player &p) {}

void Worms::Land::holy(Worms::Player &p) {}
