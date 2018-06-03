/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#include "Bazooka.h"

Weapon::Bazooka::Bazooka(float angle): Worms::Weapon(Game::Config::getInstance()
                                                             .getBazookaConfig(),
                                                     Worm::WeaponID::WBazooka,
                                                     angle){}

void Weapon::Bazooka::update(float dt) {
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
