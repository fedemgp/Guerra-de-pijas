/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#include "Cluster.h"
#include "Player.h"

Weapon::Cluster::Cluster(float angle)
    : Worms::Weapon(Game::Config::getInstance().getClusterConfig(), Worm::WeaponID::WCluster,
                    angle) {
    this->powerChargeTime = Game::Config::getInstance().getPowerChargeTime();
}

void Weapon::Cluster::update(float dt) {
    if (this->increaseShotPower) {
        if (this->shotPower < this->config.maxShotPower) {
            this->shotPower += dt / this->powerChargeTime * this->config.maxShotPower;
        }
    }
}

void Weapon::Cluster::startShot() {
    this->increaseShotPower = true;
}

void Weapon::Cluster::endShot(){
    this->increaseShotPower = false;
    this->shotPower = 0;
}

void Weapon::Cluster::setTimeout(uint8_t time) {
    this->timeLimit = time;
}
// TODO add bullets in this implementation
std::list<Worms::Bullet> Weapon::Cluster::onExplode() {
    return std::move(std::list<Worms::Bullet>());
}
