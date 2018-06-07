/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#include "Mortar.h"
#include "Player.h"

Weapon::Mortar::Mortar(float angle)
    : Worms::Weapon(Game::Config::getInstance().getMortarConfig(), Worm::WeaponID::WMortar, angle) {
}

void Weapon::Mortar::update(float dt) {
    if (this->increaseShotPower) {
        if (this->shotPower >= this->config.maxShotPower) {
            this->shotPower = this->config.maxShotPower;
        } else {
            this->shotPower++;
        }
    }
}

void Weapon::Mortar::startShot() {
    this->increaseShotPower = true;
}

void Weapon::Mortar::endShot(){
    this->increaseShotPower = false;
    this->shotPower = 0;
}

void Weapon::Mortar::setTimeout(uint8_t time) {}

std::list<Worms::Bullet> Weapon::Mortar::onExplode() {
    return std::move(std::list<Worms::Bullet>());
}
