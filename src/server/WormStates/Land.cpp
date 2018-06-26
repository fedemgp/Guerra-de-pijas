//
// Created by rodrigo on 3/06/18.
//

#include "Land.h"
#include "../Config/Config.h"
#include "../Player.h"
#include "PlayerState.h"

Worms::Land::Land()
    : State(Worm::StateID::Land), landTime(Game::Config::getInstance().getLandTime()) {}

void Worms::Land::update(Worms::Player &p, float dt, b2Body *body) {
    this->timeElapsed += dt;
    if (this->timeElapsed > this->landTime) {
        p.notify(p, Event::WormLanded);
        if (p.health <= 0) {
            p.notify(p, Event::Dying);
            p.setState(Worm::StateID::Die);
        } else {
            p.setState(Worm::StateID::Still);
        }
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

void Worms::Land::setTimeout(Worms::Player &p, uint8_t time) {}

void Worms::Land::aerialAttack(Worms::Player &p) {}

void Worms::Land::dynamite(Worms::Player &p) {}

void Worms::Land::teleport(Worms::Player &p) {}

void Worms::Land::baseballBat(Worms::Player &p) {}
