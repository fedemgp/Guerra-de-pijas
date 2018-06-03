/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#include "Mortar.h"

Weapon::Mortar::Mortar(float angle) : Worms::Weapon(Game::Config::getInstance()
                                                            .getMortarConfig(),
                                                    Worm::WeaponID::WMortar,
                                                    angle){}

void Weapon::Mortar::update(float dt){
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

