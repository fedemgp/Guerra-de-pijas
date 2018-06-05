/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 27/05/18
 */

#include <iostream>

#include "GameStateMsg.h"
#include "Weapon.h"

Worm::Weapon::Weapon(const GUI::GameTextureManager &texMgr,
                     GUI::GameTextures tex, uint16_t centerFrame, WeaponID id) :
        textureMgr(texMgr), current(id), centerFrame(centerFrame),
        weaponAnimation(texMgr.get(tex), false, centerFrame, false){}

const Worm::WeaponID &Worm::Weapon::getWeaponID() const {
    return this->current;
}
