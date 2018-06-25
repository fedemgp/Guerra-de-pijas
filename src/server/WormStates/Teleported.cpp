//
// Created by rodrigo on 16/06/18.
//

#include "Teleported.h"
#include "../Config/Config.h"
#include "../Player.h"

Worms::Teleported::Teleported()
    : State(Worm::StateID::Teleported),
      teleportTime(Game::Config::getInstance().getTeleportTime()) {}

void Worms::Teleported::update(Worms::Player &p, float dt, b2Body *body) {
    this->timeElapsed += dt;
    if (this->timeElapsed >= this->teleportTime){
        p.setState(Worm::StateID::Falling);
    }
}

void Worms::Teleported::moveRight(Worms::Player &p) {}

void Worms::Teleported::moveLeft(Worms::Player &p) {}

void Worms::Teleported::jump(Worms::Player &p) {}

void Worms::Teleported::stopMove(Worms::Player &p) {}

void Worms::Teleported::backFlip(Worms::Player &p) {}

void Worms::Teleported::bazooka(Worms::Player &p) {}

void Worms::Teleported::pointUp(Worms::Player &p) {}

void Worms::Teleported::pointDown(Worms::Player &p) {}

void Worms::Teleported::startShot(Worms::Player &p) {}

void Worms::Teleported::endShot(Worms::Player &p) {}

void Worms::Teleported::grenade(Worms::Player &p) {}

void Worms::Teleported::cluster(Worms::Player &p) {}

void Worms::Teleported::mortar(Worms::Player &p) {}

void Worms::Teleported::banana(Worms::Player &p) {}

void Worms::Teleported::holy(Worms::Player &p) {}

void Worms::Teleported::setTimeout(Worms::Player &p, uint8_t time) {}

void Worms::Teleported::aerialAttack(Worms::Player &p) {}

void Worms::Teleported::dynamite(Worms::Player &p) {}

void Worms::Teleported::teleport(Worms::Player &p) {}

void Worms::Teleported::baseballBat(Worms::Player &p) {}
