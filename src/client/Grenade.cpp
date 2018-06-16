/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#include <cmath>

#include "Grenade.h"

Worm::Grenade::Grenade(const GUI::GameTextureManager &tex)
    : Weapon(tex, GUI::GameTextures::WormGrenade, GRENADE_CENTER_FRAME, WeaponID::WGrenade),
      scope(this->textureMgr),
      powerBar(this->textureMgr) {}

void Worm::Grenade::update(float dt) {
    this->weaponAnimation.update(dt);
    this->scope.update(dt);
    this->powerBar.update(dt);
}

void Worm::Grenade::render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) {
    this->weaponAnimation.render(p, cam, flip);
    this->scope.render(p, cam, flip);
    this->powerBar.render(p, cam, flip);
}

void Worm::Grenade::setAngle(float angle, Worm::Direction d) {
    this->weaponAnimation.setFrame((int)std::ceil(angle / ANGLE_STEP) + this->centerFrame);
    this->scope.setAngle(angle, d);
    this->powerBar.setAngle(angle, d);
}

void Worm::Grenade::startShot() {
    this->powerBar.startShot();
}

void Worm::Grenade::endShot() {
    this->powerBar.endShot();
}

bool Worm::Grenade::positionSelected(){
    return false;
}
