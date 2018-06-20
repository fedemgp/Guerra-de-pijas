/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 16/06/18
 */

#include "AerialAttack.h"

Worm::AerialAttack::AerialAttack(const GUI::GameTextureManager &tex)
    : Weapon(tex, GUI::GameTextures::WormAirAttack, AERIAL_ATTACK_CENTER_FRAME, WeaponID::WAerial) {
    this->weaponAnimation.setAnimateOnce();
}

void Worm::AerialAttack::update(float dt) {
    if (!this->weaponAnimation.finished()) {
        this->weaponAnimation.update(dt);
    } else {
        this->endAnimation();
    }
}

void Worm::AerialAttack::render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) {
    this->weaponAnimation.render(p, cam, flip);
}

void Worm::AerialAttack::setAngle(float angle, Worm::Direction d) {}

void Worm::AerialAttack::startShot() {}

void Worm::AerialAttack::endShot() {}

bool Worm::AerialAttack::positionSelected() {
    this->weaponAnimation.setAutoUpdate(true);
    return true;
}

void Worm::AerialAttack::endAnimation() {
    this->weaponAnimation.setFrame(AERIAL_ATTACK_CENTER_FRAME);
    this->weaponAnimation.setAutoUpdate(false);
}
