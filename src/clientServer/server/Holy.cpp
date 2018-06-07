/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#include "Holy.h"
#include "Player.h"

Weapon::Holy::Holy(float angle)
    : Worms::Weapon(Game::Config::getInstance().getHolyConfig(), Worm::WeaponID::WHoly, angle) {
    this->powerChargeTime = Game::Config::getInstance().getPowerChargeTime();
}

void Weapon::Holy::update(float dt) {
    if (this->increaseShotPower) {
        if (this->shotPower < this->config.maxShotPower) {
            this->shotPower += dt / this->powerChargeTime * this->config.maxShotPower;
        }
    }
}

void Weapon::Holy::startShot() {
    this->increaseShotPower = true;
}

void Weapon::Holy::endShot(){
    this->increaseShotPower = false;
    this->shotPower = 0;
}

void Weapon::Holy::setTimeout(uint8_t time) {
    this->timeLimit = time;
}
// TODO add bullets
std::list<Worms::Bullet> Weapon::Holy::onExplode() {
    return std::move(std::list<Worms::Bullet>());
}
