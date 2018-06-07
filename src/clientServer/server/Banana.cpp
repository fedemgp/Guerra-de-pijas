/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#include "Banana.h"
#include "Player.h"

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

void Weapon::Banana::startShot() {
    this->increaseShotPower = true;
}

void Weapon::Banana::endShot(){
    this->increaseShotPower = false;
    //    Math::Point<float> position = p.getPosition();
    //    float safeNonContactDistance =
    //        sqrt((PLAYER_WIDTH / 2) * (PLAYER_WIDTH / 2) + (PLAYER_HEIGHT / 2) * (PLAYER_HEIGHT /
    //        2));
    //    float angle = this->angle;
    //    if (p.direction == Worms::Direction::right) {
    //        if (angle < 0.0f) {
    //            angle += 360.0f;
    //        }
    //    } else {
    //        angle = 180.0f - angle;
    //    }
    //    this->bullet = std::shared_ptr<Worms::Bullet>(new Worms::Bullet(
    //        Worms::BulletInfo{Worms::DamageInfo{this->config.damage, this->config.damageRadius},
    //        angle,
    //                          this->shotPower, p.getPosition(), safeNonContactDistance,
    //                          this->config.restitution, this->config.friction},
    //        physics, this->timeLimit));
    this->shotPower = 0;
}

void Weapon::Banana::setTimeout(uint8_t time) {
    this->timeLimit = time;
}

std::list<Worms::Bullet> Weapon::Banana::onExplode() {
    return std::move(std::list<Worms::Bullet>());
}
