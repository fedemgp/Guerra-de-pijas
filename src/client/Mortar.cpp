/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#include <cmath>

#include "Mortar.h"

Worm::Mortar::Mortar(const GUI::GameTextureManager &tex)
    : Weapon(tex, GUI::GameTextures::Bazooka2, MORTAR_CENTER_FRAME, WeaponID::WMortar),
      scope(this->textureMgr),
      powerBar(this->textureMgr) {}

void Worm::Mortar::update(float dt) {
    this->weaponAnimation.update(dt);
    this->scope.update(dt);
    this->powerBar.update(dt);
}

void Worm::Mortar::render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) {
    this->weaponAnimation.render(p, cam, flip);
    this->scope.render(p, cam, flip);
    this->powerBar.render(p, cam, flip);
}

void Worm::Mortar::setAngle(float angle, Worm::Direction d) {
    this->weaponAnimation.setFrame((int)std::ceil(angle / ANGLE_STEP) + this->centerFrame);
    this->scope.setAngle(angle, d);
    this->powerBar.setAngle(angle, d);
}

void Worm::Mortar::startShot() {
    this->powerBar.startShot();
}

void Worm::Mortar::endShot() {
    this->powerBar.endShot();
}

bool Worm::Mortar::positionSelected(){
    return false;
}
