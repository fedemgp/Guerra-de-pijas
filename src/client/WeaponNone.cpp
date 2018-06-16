/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#include "WeaponNone.h"

Worm::WeaponNone::WeaponNone(const GUI::GameTextureManager &textureManager)
    : Weapon(textureManager, GUI::GameTextures::WormIdle, 0, WeaponID::WNone) {}

void Worm::WeaponNone::update(float dt) {}

void Worm::WeaponNone::render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) {}

void Worm::WeaponNone::setAngle(float angle, Worm::Direction d) {}

void Worm::WeaponNone::startShot() {}

void Worm::WeaponNone::endShot() {}

bool Worm::WeaponNone::positionSelected(){
    return false;
}
