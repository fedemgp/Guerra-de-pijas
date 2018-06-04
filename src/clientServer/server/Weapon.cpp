/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 28/05/18
 */

#include "Weapon.h"
#include "Config.h"
#include "Player.h"

Worms::Weapon::Weapon(const Game::Weapon::Config &config, Worm::WeaponID id,
                      float angle) : config(config), id(id), angle(angle){
    this->angle = angle;
    /*
     * Because the limit angles between weapons are
     * differents, it is necesary to check boundaries angles.
     * If not, the game could crash in rendering time.
     */
    this->checkBoundaryAngles();
}

const Worm::WeaponID &Worms::Weapon::getWeaponID() const {
    return this->id;
}

void Worms::Weapon::decreaseAngle() {
    this->angle -= this->config.angleStep;
    if (this->angle < this->config.minAngle) {
        this->angle = this->config.minAngle;
    }
}

void Worms::Weapon::increaseAngle() {
    this->angle += this->config.angleStep;
    if (this->angle > this->config.maxAngle) {
        this->angle = this->config.maxAngle;
    }
}

float Worms::Weapon::getAngle() const {
    return this->angle;
}

void Worms::Weapon::destroyBullet() {
    this->bullet = nullptr;
}

std::shared_ptr<Worms::Bullet> Worms::Weapon::getBullet() const {
    return this->bullet;
}

void Worms::Weapon::checkBoundaryAngles() {
    if (this->angle > this->config.maxAngle) {
        this->angle = this->config.maxAngle;
    } else if (this->angle < this->config.minAngle) {
        this->angle = this->config.minAngle;
    }
}
