/*
 *  Created by Rodrigo.
 *  date: 21/05/18
 */

#include "Player.h"
#include "Config.h"
#include "PlayerEndBackFlip.h"
#include "PlayerState.h"

Worms::EndBackFlip::EndBackFlip()
    : State(Worm::StateID::EndBackFlip), landTime(Game::Config::getInstance().getLandTime()) {}

void Worms::EndBackFlip::update(Worms::Player &p, float dt, b2Body *body) {
    this->timeElapsed += dt;
    if (this->timeElapsed > this->landTime) {
        p.setState(Worm::StateID::Still);
    }
}

void Worms::EndBackFlip::moveRight(Worms::Player &p) {}

void Worms::EndBackFlip::moveLeft(Worms::Player &p) {}

void Worms::EndBackFlip::jump(Worms::Player &p) {}

void Worms::EndBackFlip::stopMove(Worms::Player &p) {}

void Worms::EndBackFlip::backFlip(Worms::Player &p) {}

void Worms::EndBackFlip::bazooka(Worms::Player &p) {}

void Worms::EndBackFlip::pointUp(Worms::Player &p) {}

void Worms::EndBackFlip::pointDown(Worms::Player &p) {}

void Worms::EndBackFlip::startShot(Worms::Player &p) {}

void Worms::EndBackFlip::endShot(Worms::Player &p) {}

void Worms::EndBackFlip::grenade(Worms::Player &p) {}

void Worms::EndBackFlip::cluster(Worms::Player &p) {}

void Worms::EndBackFlip::mortar(Worms::Player &p) {}

void Worms::EndBackFlip::banana(Worms::Player &p) {}

void Worms::EndBackFlip::holy(Worms::Player &p) {}

void Worms::EndBackFlip::setTimeout(Worms::Player &p, uint8_t time) {}

void Worms::EndBackFlip::aerialAttack(Worms::Player &p){}
