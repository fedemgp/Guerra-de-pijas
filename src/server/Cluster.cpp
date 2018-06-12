/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#include "Cluster.h"

Weapon::Cluster::Cluster(float angle)
    : Worms::Weapon(Game::Config::getInstance().getClusterConfig(), Worm::WeaponID::WCluster,
                    angle), fragmentConfig(Game::Config::getInstance().getClusterFragmentConfig()) {
    this->powerChargeTime = Game::Config::getInstance().getPowerChargeTime();
}

void Weapon::Cluster::update(float dt) {
    if (this->increaseShotPower) {
        if (this->shotPower < this->config.maxShotPower) {
            this->shotPower += dt / this->powerChargeTime * this->config.maxShotPower;
        }
    }
}

void Weapon::Cluster::startShot(Worms::Player *player) {
    this->increaseShotPower = true;
}

void Weapon::Cluster::endShot(){
      this->increaseShotPower = false;
    this->shotPower = 0;
}

void Weapon::Cluster::setTimeout(uint8_t time) {
    this->timeLimit = time;
}

std::list<Worms::Bullet> Weapon::Cluster::onExplode(const Worms::Bullet &mainBullet, Worms::Physics &physics) {
    uint8_t fragmentQuantity = Game::Config::getInstance()
            .getClusterFragmentQuantity();
    Math::Point<float> p = mainBullet.getPosition();
    Worms::BulletInfo bulletInfo = {this->fragmentConfig.dmgInfo,
                           p,this->fragmentConfig.minAngle,
                           (float)this->fragmentConfig.maxShotPower,
                            this->fragmentConfig.bulletRadius * 6, this->fragmentConfig.restitution,
                           this->fragmentConfig.friction,
                           this->fragmentConfig.explotionInitialTimeout,
                                    Event::Explode, this->fragmentConfig.bulletRadius, this->fragmentConfig.bulletDampingRatio};

    std::list<Worms::Bullet> ret;
    for (int i = 0; i < fragmentQuantity; i++){
        bulletInfo.angle =  i * this->fragmentConfig.angleStep + this->fragmentConfig.minAngle;
        ret.emplace_back(bulletInfo, physics, Worm::WeaponID::WFragment);
    }

    return std::move(ret);
}

void
Weapon::Cluster::positionSelected(Worms::Player &p, Math::Point<float> point){}
