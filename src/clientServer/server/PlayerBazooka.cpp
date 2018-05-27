//
// Created by rodrigo on 21/05/18.
//

#include <iostream>
#include "PlayerBazooka.h"
#include "Player.h"
/*
 * TODO add previous and finish states of bazooka, using wbazbak.png and wbazink.png
 */
Worms::Bazooka::Bazooka() : State(Worm::StateID::Bazooka) {}

void Worms::Bazooka::update(Worms::Player &p, float dt, b2Body *body){
    if (this->increaseShotPower) {
        if(this->shotPower == MAX_SHOT_POWER) {
            this->shotPower = 0;
        } else {
            this->shotPower++;
        }
    }
}

void Worms::Bazooka::moveRight(Worms::Player &p) {
    if (p.direction == Direction::right) {
        p.setState(Worm::StateID::Walk);
    }
    p.direction = Direction::right;
}

void Worms::Bazooka::moveLeft(Worms::Player &p) {
    if (p.direction == Direction::left) {
        p.setState(Worm::StateID::Walk);
    }
    p.direction = Direction::left;
}

void Worms::Bazooka::jump(Worms::Player &p) {}

void Worms::Bazooka::stopMove(Worms::Player &p) {}

void Worms::Bazooka::bazooka(Worms::Player &p) {}

void Worms::Bazooka::pointUp(Worms::Player &p){
    p.increaseAngle();
}

void Worms::Bazooka::pointDown(Worms::Player &p){
    p.decreaseAngle();
}

void Worms::Bazooka::backFlip(Worms::Player &p) {
    p.setState(Worm::StateID::StartBackFlip);
}

void Worms::Bazooka::startShot(Worms::Player &p) {
    this->increaseShotPower = true;
}

void Worms::Bazooka::endShot(Worms::Player &p) {
    this->increaseShotPower = false;
    p.shoot(this->shotPower);
    p.setState(Worm::StateID::Still);
}
