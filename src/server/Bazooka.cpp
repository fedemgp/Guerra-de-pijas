/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#include "Bazooka.h"
#include "Player.h"

Weapon::Bazooka::Bazooka(float angle)
    : Worms::Weapon(Game::Config::getInstance().getBazookaConfig(), Worm::WeaponID::WBazooka,
                    angle) {
    this->powerChargeTime = Game::Config::getInstance().getPowerChargeTime();
}

void Weapon::Bazooka::update(float dt) {
    if (this->increaseShotPower) {
        if (this->shotPower < this->config.maxShotPower) {
            this->shotPower += dt / this->powerChargeTime * this->config.maxShotPower;
        } else {
            this->player->endShot();
        }
    }
}

void Weapon::Bazooka::startShot(Worms::Player *player) {
    this->increaseShotPower = true;
    this->player = player;
}

void Weapon::Bazooka::endShot(){
    this->increaseShotPower = false;
    this->shotPower = 0;
}

void Weapon::Bazooka::setTimeout(uint8_t time) {}

std::list<Worms::Bullet> Weapon::Bazooka::onExplode(const Worms::Bullet &mainBullet, Worms::Physics &physics) {
    return std::move(std::list<Worms::Bullet>());
}

void
Weapon::Bazooka::positionSelected(Worms::Player &p, Math::Point<float> point){}
