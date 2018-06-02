/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 28/05/18
 */

#include "Weapon.h"
#include "Player.h"
#include "Config.h"

Worms::Weapon::Weapon(): minAngle(Game::Config::getInstance().getMinAngle()),
                         maxAngle(Game::Config::getInstance().getMaxAngle()),
                         angleStep(Game::Config::getInstance().getAngleStep()),
                         maxPowerShot(Game::Config::getInstance()
                                              .getMaxShotPower()){

}

const Worm::WeaponID &Worms::Weapon::getWeaponID() const {
    return this->id;
}

void Worms::Weapon::update(float dt) {
    if (this->increaseShotPower) {
        if (this->shotPower >= this->maxPowerShot) {
            this->shotPower = this->maxPowerShot;
        } else {
            this->shotPower++;
        }
    }
}

void Worms::Weapon::setWeaponID(const Worm::WeaponID &id) {
    this->id = id;
}

void Worms::Weapon::decreaseAngle() {
    this->angle -= this->angleStep;
    if (this->angle < this->minAngle) {
        this->angle = this->minAngle;
    }
}

void Worms::Weapon::increaseAngle() {
    this->angle += this->angleStep;
    if (this->angle > this->maxAngle) {
        this->angle = this->maxAngle;
    }
}

float Worms::Weapon::getAngle() const {
    return this->angle;
}

void Worms::Weapon::startShot() {
    this->increaseShotPower = true;
}

void Worms::Weapon::endShot(Worms::Player &p) {
    this->increaseShotPower = false;
    p.shoot(this->shotPower);
    this->shotPower = 0;
}
