/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#include <cmath>

#include "Holy.h"

Worm::Holy::Holy(const GUI::GameTextureManager &tex)
    : Weapon(tex, GUI::GameTextures::WormHoly, HOLY_CENTER_FRAME, WeaponID::WHoly),
      scope(this->textureMgr),
      powerBar(this->textureMgr) {}

void Worm::Holy::update(float dt) {
    this->weaponAnimation.update(dt);
    this->scope.update(dt);
    this->powerBar.update(dt);
}

void Worm::Holy::render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) {
    this->weaponAnimation.render(p, cam, flip);
    this->scope.render(p, cam, flip);
    this->powerBar.render(p, cam, flip);
}

void Worm::Holy::setAngle(float angle, Worm::Direction d) {
    this->weaponAnimation.setFrame((int)std::ceil(angle / ANGLE_STEP) + this->centerFrame);
    this->scope.setAngle(angle, d);
    this->powerBar.setAngle(angle, d);
}

void Worm::Holy::startShot() {
    this->powerBar.startShot();
}

void Worm::Holy::endShot() {
    this->powerBar.endShot();
}

bool Worm::Holy::positionSelected() {
    return false;
}
