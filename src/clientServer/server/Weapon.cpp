/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 28/05/18
 */

#include "Weapon.h"

const Worm::WeaponID &Worms::Weapon::getWeaponID() const{
    return this->id;
}

void Worms::Weapon::setWeaponID(const Worm::WeaponID &id){
    this->id = id;
}
