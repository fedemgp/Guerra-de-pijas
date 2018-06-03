/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 28/05/18
 */

#include "Weapon.h"
#include "Player.h"
#include "Config.h"

Worms::Weapon::Weapon(): config(Game::Config::getInstance().getBazookaConfig()){
}

const Worm::WeaponID &Worms::Weapon::getWeaponID() const {
    return this->id;
}

void Worms::Weapon::update(float dt) {
    if (this->increaseShotPower) {
        if (this->shotPower >= this->config.maxShotPower) {
            this->shotPower = this->config.maxShotPower;
        } else {
            this->shotPower++;
        }
    }

    if (this->bullet != nullptr) {
        this->bullet->update(dt);
        //        if (this->bullet->madeImpact()) {
        //            this->bullet = nullptr;
        //        }
        if (this->bullet->getPosition().y <
                Game::Config::getInstance().getWaterLevel()) {
            this->bullet = nullptr;
        }
    }
}

void Worms::Weapon::setWeapon(const Worm::WeaponID &id) {
    if (this->id != id){
        this->id = id;
        switch (id){
            case Worm::WeaponID::WBazooka:
                this->config = Game::Config::getInstance().getBazookaConfig();
                break;
            case Worm::WeaponID::WGrenade:
                this->config = Game::Config::getInstance().getGreenGrenadeConfig();
                break;
            case Worm::WeaponID::WCluster:
                this->config = Game::Config::getInstance().getClusterConfig();
                break;
            case Worm::WeaponID::WMortar:
                this->config = Game::Config::getInstance().getMortarConfig();
                break;
            case Worm::WeaponID::WBanana:
                this->config = Game::Config::getInstance().getBananaConfig();
                break;
            case Worm::WeaponID::WNone:
                break;
        }
        /*
         * Because the limit angles between weapons are
         * differents, it is necesary to check boundaries angles.
         * If not, the game could crash in rendering time.
         */
        this->checkBoundaryAngles();

    }
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

void Worms::Weapon::startShot() {
    this->increaseShotPower = true;
}

void Worms::Weapon::endShot(Worms::Player &p, Physics &physics) {
    this->increaseShotPower = false;
    Math::Point<float> position = p.getPosition();
    float safeNonContactDistance =
            sqrt((PLAYER_WIDTH / 2) * (PLAYER_WIDTH / 2) + (PLAYER_HEIGHT / 2) * (PLAYER_HEIGHT / 2));
    float angle = this->angle;
    if (p.direction == Direction::right) {
        if (angle < 0.0f) {
            angle += 360.0f;
        }
    } else {
        angle = 180.0f - angle;
    }
    this->bullet = std::shared_ptr<Worms::Bullet>(
            new Worms::Bullet(BulletInfo {
                    DamageInfo{this->config.damage, this->config.damageRadius},
                    angle, this->shotPower, p.getPosition(),
                    safeNonContactDistance}, physics));
    this->shotPower = 0;
}

void Worms::Weapon::destroyBullet(){
    this->bullet = nullptr;
}

std::shared_ptr<Worms::Bullet> Worms::Weapon::getBullet() const{
    return this->bullet;
}

void Worms::Weapon::checkBoundaryAngles(){
    if (this->angle > this->config.maxAngle){
        this->angle = this->config.maxAngle;
    } else if (this->angle < this->config.minAngle){
        this->angle = this->config.minAngle;
    }
}
