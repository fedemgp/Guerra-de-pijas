/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 28/05/18
 */

#include "Weapon.h"
#include "Config.h"
#include "Player.h"

Worms::Weapon::Weapon(const Game::Weapon::Config &config, Worm::WeaponID id, float angle)
    : config(config), id(id), angle(angle) {
    this->angle = angle;
    this->timeLimit = this->config.explotionInitialTimeout;
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

void Worms::Weapon::checkBoundaryAngles() {
    if (this->angle > this->config.maxAngle) {
        this->angle = this->config.maxAngle;
    } else if (this->angle < this->config.minAngle) {
        this->angle = this->config.minAngle;
    }
}

Worms::BulletInfo Worms::Weapon::getBulletInfo() {
    return Worms::BulletInfo{this->config.dmgInfo,
                             Math::Point<float>{0, 0},
                             angle,
                             this->shotPower,
                             0,
                             this->config.restitution,
                             this->config.friction,
                             this->timeLimit,
                             this->config.hasAfterExplode ? Event::OnExplode :
                                Event::Explode,
                             this->config.bulletRadius
    };
}
