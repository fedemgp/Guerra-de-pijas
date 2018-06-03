/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#include "Banana.h"

Weapon::Banana::Banana(float angle) : Worms::Weapon(Game::Config::getInstance()
                                                            .getBananaConfig(),
                                                    Worm::WeaponID::WBanana,
                                                    angle){}

void Weapon::Banana::update(float dt){
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
