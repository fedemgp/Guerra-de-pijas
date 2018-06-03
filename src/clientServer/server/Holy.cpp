/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#include "Holy.h"

Weapon::Holy::Holy(float angle) : Worms::Weapon(Game::Config::getInstance()
                                                        .getHolyConfig(),
                                                Worm::WeaponID::WHoly, angle){}

void Weapon::Holy::update(float dt){
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
