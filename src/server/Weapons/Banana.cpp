/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#include "Banana.h"
#include "../Player.h"

Weapon::Banana::Banana(float angle)
    : Worms::Weapon(Game::Config::getInstance().getBananaConfig(), Worm::WeaponID::WBanana, angle) {
    this->powerChargeTime = Game::Config::getInstance().getPowerChargeTime();
}

void Weapon::Banana::update(float dt) {
    if (this->increaseShotPower) {
        if (this->shotPower < this->config.maxShotPower) {
            this->shotPower += dt / this->powerChargeTime * this->config.maxShotPower;
        }
    }
}

void Weapon::Banana::startShot(Worms::Player *player) {
    this->increaseShotPower = true;
}

void Weapon::Banana::endShot() {
    this->increaseShotPower = false;
    this->shotPower = 0;
}

void Weapon::Banana::setTimeout(uint8_t time) {
    this->timeLimit = time;
}

std::list<Worms::Bullet> Weapon::Banana::onExplode(const Worms::Bullet &mainBullet,
                                                   Worms::Physics &physics) {
    return std::move(std::list<Worms::Bullet>());
}

void Weapon::Banana::positionSelected(Worms::Player &p, Math::Point<float> point) {}
