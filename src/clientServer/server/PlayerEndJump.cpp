/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 20/05/18
 */

#include "Config.h"
#include "PlayerEndJump.h"
#include "Player.h"

Worms::EndJump::EndJump() : State(Worm::StateID::EndJump),
                            landTime(Game::Config::getInstance()
                                             .getLandTime()) {}

void Worms::EndJump::update(Worms::Player &p, float dt, b2Body *body) {
    this->timeElapsed += dt;
    if (this->timeElapsed > this->landTime) {
        p.setState(Worm::StateID::Still);
    }
}

void Worms::EndJump::moveRight(Worms::Player &p) {}

void Worms::EndJump::moveLeft(Worms::Player &p) {}

void Worms::EndJump::jump(Worms::Player &p) {}

void Worms::EndJump::stopMove(Worms::Player &p) {}

void Worms::EndJump::bazooka(Worms::Player &p) {}

void Worms::EndJump::pointUp(Worms::Player &p) {}

void Worms::EndJump::pointDown(Worms::Player &p) {}

void Worms::EndJump::backFlip(Worms::Player &p) {}

void Worms::EndJump::startShot(Worms::Player &p) {}

void Worms::EndJump::endShot(Worms::Player &p) {}
