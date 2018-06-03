/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 27/05/18
 */

#include <cmath>

#include "GameStateMsg.h"
#include "Weapon.h"

Worm::Weapon::Weapon(const GUI::GameTextureManager &tex) : textureMgr(tex) {
    //    this->animations.emplace_back(this->textureMgr.get(GUI::GameTextures::WormIdle), true);
}

void Worm::Weapon::update(float dt) {
    for (auto &animation : this->animations) {
        animation.update(dt);
    }
}

void Worm::Weapon::render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) {
    for (auto &animation : this->animations) {
        animation.render(p, cam, flip);
    }
}

void Worm::Weapon::setWeapon(const WeaponID &id) {
    if (id != this->current) {
        // Clean previous animation
        this->current = id;
        this->animations.erase(this->animations.begin(), this->animations.end());
        this->weaponAnimation = nullptr;
        switch (id) {
            case WeaponID::WBazooka:
                this->centerFrame = BAZOOKA_CENTER_FRAME;
                this->animations.emplace_back(this->textureMgr.get(GUI::GameTextures::Bazooka),
                                              true, this->centerFrame, false);
                this->weaponAnimation = &this->animations.back();
                break;
            case WeaponID::WGrenade:
                this->centerFrame = GRENADE_CENTER_FRAME;
                this->animations.emplace_back(this->textureMgr.get(GUI::GameTextures::WormGrenade),
                                              true, this->centerFrame, false);
                this->weaponAnimation = &this->animations.back();
                break;
            case WeaponID::WCluster:
                this->centerFrame = GRENADE_CENTER_FRAME;
                this->animations.emplace_back(this->textureMgr.get(GUI::GameTextures::WormCluster),
                                              true, this->centerFrame, false);
                this->weaponAnimation = &this->animations.back();
                break;
            case WeaponID::WMortar:
                this->centerFrame = BAZOOKA_CENTER_FRAME;
                this->animations.emplace_back(this->textureMgr.get(GUI::GameTextures::Bazooka2),
                                              true, this->centerFrame, false);
                this->weaponAnimation = &this->animations.back();
                break;
            case WeaponID::WBanana:
                this->centerFrame = BANANA_CENTER_FRAME;
                this->animations.emplace_back(this->textureMgr.get(GUI::GameTextures::WormBanana),
                                              true, this->centerFrame, false);
                this->weaponAnimation = &this->animations.back();
                break;
            case WeaponID::WHoly:
                this->centerFrame = HOLY_CENTER_FRAME;
                this->animations.emplace_back(this->textureMgr.get(GUI::GameTextures::WormHoly),
                                              true, this->centerFrame, false);
                this->weaponAnimation = &this->animations.back();
                break;
            case WeaponID::WNone:
                break;
        }
    }
}

const Worm::WeaponID &Worm::Weapon::getWeaponID() const {
    return this->current;
}

void Worm::Weapon::setAngle(float angle) {
    this->weaponAnimation->setFrame((int)std::ceil(angle / ANGLE_STEP) + this->centerFrame);
}
