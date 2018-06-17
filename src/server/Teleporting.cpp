//
// Created by rodrigo on 16/06/18.
//

#include <Camera.h>
#include "Config.h"
#include "Player.h"
#include "Teleporting.h"

Worms::Teleporting::Teleporting(GUI::Position p) : State(Worm::StateID::Teleporting), newPosition(p), teleportTime(Game::Config::getInstance().getTeleportTime()) {}

void Worms::Teleporting::update(Worms::Player &p, float dt, b2Body *body) {
    this->timeElapsed += dt;
    if (this->timeElapsed >= this->teleportTime) {
        p.setPosition(this->newPosition);
        p.setState(Worm::StateID::Teleported);
    }
}

void Worms::Teleporting::moveRight(Worms::Player &p) {}

void Worms::Teleporting::moveLeft(Worms::Player &p) {}

void Worms::Teleporting::jump(Worms::Player &p) {}

void Worms::Teleporting::stopMove(Worms::Player &p) {}

void Worms::Teleporting::backFlip(Worms::Player &p) {}

void Worms::Teleporting::bazooka(Worms::Player &p) {}

void Worms::Teleporting::pointUp(Worms::Player &p) {}

void Worms::Teleporting::pointDown(Worms::Player &p) {}

void Worms::Teleporting::startShot(Worms::Player &p) {}

void Worms::Teleporting::endShot(Worms::Player &p) {}

void Worms::Teleporting::grenade(Worms::Player &p) {}

void Worms::Teleporting::cluster(Worms::Player &p) {}

void Worms::Teleporting::mortar(Worms::Player &p) {}

void Worms::Teleporting::banana(Worms::Player &p) {}

void Worms::Teleporting::holy(Worms::Player &p) {}

void Worms::Teleporting::setTimeout(Worms::Player &p, uint8_t time) {}

void Worms::Teleporting::aerialAttack(Worms::Player &p) {}

void Worms::Teleporting::dynamite(Worms::Player &p) {}

void Worms::Teleporting::teleport(Worms::Player &p) {}
