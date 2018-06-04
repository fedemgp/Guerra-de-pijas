/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#include "Mortar.h"
#include "Player.h"

Weapon::Mortar::Mortar(float angle)
    : Worms::Weapon(Game::Config::getInstance().getMortarConfig(), Worm::WeaponID::WMortar, angle) {
}

void Weapon::Mortar::update(float dt) {
    if (this->increaseShotPower) {
        if (this->shotPower >= this->config.maxShotPower) {
            this->shotPower = this->config.maxShotPower;
        } else {
            this->shotPower++;
        }
    }

    if (this->bullet != nullptr) {
        this->bullet->update(dt, *this);
    }
}

void Weapon::Mortar::startShot() {
    this->increaseShotPower = true;
}

void Weapon::Mortar::endShot(Worms::Player &p, Worms::Physics &physics) {
    this->increaseShotPower = false;
    Math::Point<float> position = p.getPosition();
    float safeNonContactDistance =
        sqrt((PLAYER_WIDTH / 2) * (PLAYER_WIDTH / 2) + (PLAYER_HEIGHT / 2) * (PLAYER_HEIGHT / 2));
    float angle = this->angle;
    if (p.direction == Worms::Direction::right) {
        if (angle < 0.0f) {
            angle += 360.0f;
        }
    } else {
        angle = 180.0f - angle;
    }
    this->bullet = std::shared_ptr<Worms::Bullet>(new Worms::Bullet(
        Worms::BulletInfo{Worms::DamageInfo{this->config.damage, this->config.damageRadius}, angle,
                          this->shotPower, p.getPosition(), safeNonContactDistance,
                          this->config.restitution, this->config.friction},
        physics));
    this->shotPower = 0;
}

void Weapon::Mortar::setTimeout(uint8_t time){}
