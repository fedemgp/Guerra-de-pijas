//
// Created by rodrigo on 16/06/18.
//

#include "BaseballBat.h"
#include <cmath>
#include <iostream>

Worm::BaseballBat::BaseballBat(const GUI::GameTextureManager &tex)
    : Weapon(tex, GUI::GameTextures::WormBaseballBat, BASEBALL_BAT_CENTER_FRAME,
             WeaponID::WBaseballBat),
      scope(this->textureMgr) {}

void Worm::BaseballBat::update(float dt) {
    this->weaponAnimation.update(dt);
    this->scope.update(dt);
}

void Worm::BaseballBat::render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) {
    this->weaponAnimation.render(p, cam, flip);
    this->scope.render(p, cam, flip);
}

void Worm::BaseballBat::setAngle(float angle, Direction d) {
    this->weaponAnimation.setFrame((int)std::ceil(angle / ANGLE_STEP) + this->centerFrame);
    this->scope.setAngle(angle, d);
}

void Worm::BaseballBat::startShot() {}

void Worm::BaseballBat::endShot() {}

bool Worm::BaseballBat::positionSelected() {
    return false;
}
