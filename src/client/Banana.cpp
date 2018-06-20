/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#include <cmath>

#include "Banana.h"

Worm::Banana::Banana(const GUI::GameTextureManager &tex)
    : Weapon(tex, GUI::GameTextures::WormBanana, BANANA_CENTER_FRAME, WeaponID::WBanana),
      scope(this->textureMgr),
      powerBar(this->textureMgr) {}

void Worm::Banana::update(float dt) {
    this->weaponAnimation.update(dt);
    this->scope.update(dt);
    this->powerBar.update(dt);
}

void Worm::Banana::render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) {
    this->weaponAnimation.render(p, cam, flip);
    this->scope.render(p, cam, flip);
    this->powerBar.render(p, cam, flip);
}

void Worm::Banana::setAngle(float angle, Worm::Direction d) {
    this->weaponAnimation.setFrame((int)std::ceil(angle / ANGLE_STEP) + this->centerFrame);
    this->scope.setAngle(angle, d);
    this->powerBar.setAngle(angle, d);
}

void Worm::Banana::startShot() {
    this->powerBar.startShot();
}

void Worm::Banana::endShot() {
    this->powerBar.endShot();
}

bool Worm::Banana::positionSelected() {
    return false;
}
