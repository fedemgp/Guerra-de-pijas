/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#include <cmath>

#include "Bazooka.h"

Worm::Bazooka::Bazooka(const GUI::GameTextureManager &tex)
    : Weapon(tex, GUI::GameTextures::Bazooka, BAZOOKA_CENTER_FRAME, WeaponID::WBazooka),
      scope(this->textureMgr),
      powerBar(this->textureMgr) {}

void Worm::Bazooka::update(float dt) {
    this->weaponAnimation.update(dt);
    this->scope.update(dt);
    this->powerBar.update(dt);
}

void Worm::Bazooka::render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) {
    this->weaponAnimation.render(p, cam, flip);
    this->scope.render(p, cam, flip);
    this->powerBar.render(p, cam, flip);
}

void Worm::Bazooka::setAngle(float angle, Direction d) {
    this->weaponAnimation.setFrame((int)std::ceil(angle / ANGLE_STEP) + this->centerFrame);
    this->scope.setAngle(angle, d);
    this->powerBar.setAngle(angle, d);
}

void Worm::Bazooka::startShot() {
    this->powerBar.startShot();
}

void Worm::Bazooka::endShot() {
    this->powerBar.endShot();
}

bool Worm::Bazooka::positionSelected() {
    return false;
}
