/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#include "Bullet.h"
#include <cmath>
#include <iostream>

Ammo::Bullet::Bullet(const GUI::GameTextureManager &texture_mgr, Worm::WeaponID id)
    : texture_mgr(texture_mgr), animation(
        this->texture_mgr.get(GUI::GameTextures::Missile), true,
        MISSILE_0_DEG_FRAME, false){
    switch (id){
        case Worm::WeaponID::WBazooka:
            this->animation = GUI::Animation(
                    this->texture_mgr.get(GUI::GameTextures::Missile), true,
                    MISSILE_0_DEG_FRAME, false);
            break;
        case Worm::WeaponID::WGrenade:
            this->animation = GUI::Animation(
                    this->texture_mgr.get(GUI::GameTextures::Grenade), false,
                    MISSILE_0_DEG_FRAME, false);
            break;
        case Worm::WeaponID::WCluster:
            this->animation = GUI::Animation(
                    this->texture_mgr.get(GUI::GameTextures::Cluster), false,
                    MISSILE_0_DEG_FRAME, false);
            break;
        case Worm::WeaponID::WMortar:
            this->animation = GUI::Animation(
                    this->texture_mgr.get(GUI::GameTextures::Mortar), false,
                    MISSILE_0_DEG_FRAME, false);
            break;
        case Worm::WeaponID::WNone:
            break;
    }
}

void Ammo::Bullet::update(float dt) {
    if (this->updateManually){
        this->animation.setFrame((int)std::floor((this->angle - 90) / MISSILE_ANGLE_STEP));
    } else {
        this->animation.update(dt);
    }
}

void Ammo::Bullet::render(GUI::Position p, GUI::Camera &cam) {
    //    if (this->direction == Direction::left) {
    //        this->animation.setFlip(SDL_FLIP_NONE);
    //    } else {
    //        this->animation.setFlip(SDL_FLIP_HORIZONTAL);
    //    }
    this->animation.render(p, cam, SDL_FLIP_HORIZONTAL);
}

void Ammo::Bullet::setAngle(float angle) {
    this->angle = angle;
}
