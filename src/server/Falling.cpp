//
// Created by rodrigo on 3/06/18.
//

#include "Falling.h"

Worms::Falling::Falling(GUI::Position p) : State(Worm::StateID::Falling), startPosition(p) {}

void Worms::Falling::update(Player &p, float dt, b2Body *body) {
    if (p.isOnGround()) {
        p.landDamage(this->startPosition.y - p.getPosition().y);
        p.setState(Worm::StateID::Land);
    }
}

void Worms::Falling::moveRight(Worms::Player &p) {}

void Worms::Falling::moveLeft(Worms::Player &p) {}

void Worms::Falling::jump(Worms::Player &p) {}

void Worms::Falling::stopMove(Worms::Player &p) {}

void Worms::Falling::backFlip(Worms::Player &p) {}

void Worms::Falling::bazooka(Worms::Player &p) {}

void Worms::Falling::pointUp(Worms::Player &p) {}

void Worms::Falling::pointDown(Worms::Player &p) {}

void Worms::Falling::startShot(Worms::Player &p) {}

void Worms::Falling::endShot(Worms::Player &p) {}

void Worms::Falling::grenade(Worms::Player &p) {}

void Worms::Falling::cluster(Worms::Player &p) {}

void Worms::Falling::mortar(Worms::Player &p) {}

void Worms::Falling::banana(Worms::Player &p) {}

void Worms::Falling::holy(Worms::Player &p) {}

void Worms::Falling::setTimeout(Worms::Player &p, uint8_t time) {}

void Worms::Falling::aerialAttack(Worms::Player &p) {}

void Worms::Falling::dynamite(Worms::Player &p){}

void Worms::Falling::teleport(Worms::Player &p) {}
