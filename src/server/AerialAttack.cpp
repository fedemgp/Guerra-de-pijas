/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 16/06/18
 */

#include "AerialAttack.h"
#define CONFIG Game::Config::getInstance()

Weapon::AerialAttack::AerialAttack()
    : Weapon::Weapon(CONFIG.getAerialAttackConfig(), Worm::WeaponID::WAerial, 0.0),
      bulletsQuantity(CONFIG.getAerialAttackMissileQuantity()),
      missileSeparation(CONFIG.getAerialAttackMissileSeparation()) {}

void Weapon::AerialAttack::update(float dt) {}

void Weapon::AerialAttack::startShot(Worms::Player *player) {}

void Weapon::AerialAttack::endShot() {}

void Weapon::AerialAttack::setTimeout(uint8_t time) {}

std::list<Worms::Bullet> Weapon::AerialAttack::onExplode(const Worms::Bullet &mainBullet,
                                                         Worms::Physics &physics) {
    return std::move(std::list<Worms::Bullet>());
}

void Weapon::AerialAttack::positionSelected(Worms::Player &p, Math::Point<float> point) {
    point.y += CONFIG.getAerialAttackLaunchHeight();
    point.x -= this->missileSeparation * (this->bulletsQuantity + 1) / 2;

    Worms::BulletInfo bulletInfo = {this->config.dmgInfo,
                                    point,
                                    this->config.minAngle,
                                    (float)this->config.maxShotPower,
                                    0,
                                    this->config.restitution,
                                    this->config.friction,
                                    this->config.explotionInitialTimeout,
                                    Event::Explode,
                                    this->config.bulletRadius,
                                    this->config.bulletDampingRatio};

    std::list<Worms::Bullet> ret;
    for (int i = 0; i < this->bulletsQuantity; i++) {
        point.x += this->missileSeparation;
        bulletInfo.point = point;
        ret.emplace_back(bulletInfo, p.getPhysics(), Worm::WeaponID::WAerial);
    }

    p.endShot(ret);
}
