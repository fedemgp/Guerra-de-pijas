/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 28/05/18
 */

#include "Weapon.h"
#include "Player.h"

const Worm::WeaponID &Worms::Weapon::getWeaponID() const {
    return this->id;
}

void Worms::Weapon::update(float dt) {
    if (this->increaseShotPower) {
        if (this->shotPower >= MAX_SHOT_POWER) {
            this->shotPower = MAX_SHOT_POWER;
        } else {
            this->shotPower++;
        }
    }
}

void Worms::Weapon::setWeaponID(const Worm::WeaponID &id) {
    this->id = id;
}

void Worms::Weapon::decreaseAngle() {
    this->angle -= ANGLE_STEP;
    if (this->angle < MIN_ANGLE) {
        this->angle = MIN_ANGLE;
    }
}

void Worms::Weapon::increaseAngle() {
    this->angle += ANGLE_STEP;
    if (this->angle > MAX_ANGLE) {
        this->angle = MAX_ANGLE;
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
