/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#include "Mortar.h"
#include "../Player.h"

Weapon::Mortar::Mortar(float angle)
    : Worms::Weapon(Game::Config::getInstance().getMortarConfig(), Worm::WeaponID::WMortar, angle),
      fragmentConfig(Game::Config::getInstance().getMortarFragmentConfig()) {}

void Weapon::Mortar::update(float dt) {
    if (this->increaseShotPower) {
        if (this->shotPower >= this->config.maxShotPower) {
            this->shotPower = this->config.maxShotPower;
        } else {
            this->shotPower++;
        }
    }
}

void Weapon::Mortar::startShot(Worms::Player *player) {
    this->increaseShotPower = true;
}

void Weapon::Mortar::endShot() {
    this->increaseShotPower = false;
    this->shotPower = 0;
}

void Weapon::Mortar::setTimeout(uint8_t time) {}

std::list<Worms::Bullet> Weapon::Mortar::onExplode(const Worms::Bullet &mainBullet,
                                                   Worms::Physics &physics) {
    uint8_t fragmentQuantity = Game::Config::getInstance().getMortarFragmentQuantity();
    Math::Point<float> p = mainBullet.getPosition();
    Worms::BulletInfo bulletInfo = {this->fragmentConfig.dmgInfo,
                                    p,
                                    this->fragmentConfig.minAngle,
                                    (float)this->fragmentConfig.maxShotPower,
                                    this->fragmentConfig.bulletRadius * 6,
                                    this->fragmentConfig.restitution,
                                    this->fragmentConfig.friction,
                                    this->fragmentConfig.explotionInitialTimeout,
                                    Event::Explode,
                                    this->fragmentConfig.bulletRadius,
                                    this->fragmentConfig.bulletDampingRatio,
                                    this->config.windAffected};

    std::list<Worms::Bullet> ret;
    for (int i = 0; i < fragmentQuantity; i++) {
        bulletInfo.angle = i * this->fragmentConfig.angleStep + this->fragmentConfig.minAngle;
        ret.emplace_back(bulletInfo, physics, Worm::WeaponID::WFragment);
    }

    return std::move(ret);
}

void Weapon::Mortar::positionSelected(Worms::Player &p, Math::Point<float> point) {}
