/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#include "Grenade.h"

Weapon::Grenade::Grenade(float angle) : Worms::Weapon(Game::Config::getInstance()
                                                              .getGreenGrenadeConfig(),
                                                      Worm::WeaponID::WGrenade,
                                                      angle){}

void Weapon::Grenade::update(float dt){
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
