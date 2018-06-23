/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#include "../Player.h"
#include "Grenade.h"

Weapon::Grenade::Grenade(float angle)
    : Worms::Weapon(Game::Config::getInstance().getGreenGrenadeConfig(), Worm::WeaponID::WGrenade,
                    angle) {
    this->powerChargeTime = Game::Config::getInstance().getPowerChargeTime();
}

void Weapon::Grenade::update(float dt) {
    if (this->increaseShotPower) {
        if (this->shotPower < this->config.maxShotPower) {
            this->shotPower += dt / this->powerChargeTime * this->config.maxShotPower;
        }
    }
}

void Weapon::Grenade::startShot(Worms::Player *player) {
    this->increaseShotPower = true;
}

void Weapon::Grenade::endShot() {
    this->increaseShotPower = false;
    this->shotPower = 0;
}

void Weapon::Grenade::setTimeout(uint8_t time) {
    this->timeLimit = time;
}

std::list<Worms::Bullet> Weapon::Grenade::onExplode(const Worms::Bullet &bullet,
                                                    Worms::Physics &physics) {
    return std::move(std::list<Worms::Bullet>());
}

void Weapon::Grenade::positionSelected(Worms::Player &p, Math::Point<float> point) {}
