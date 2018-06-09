/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#include <cmath>
#include <iostream>

#include "Bullet.h"

Ammo::Bullet::Bullet(const GUI::GameTextureManager &texture_mgr, Worm::WeaponID id)
    : texture_mgr(texture_mgr),
      animation(this->texture_mgr.get(GUI::GameTextures::Missile), true, MISSILE_0_DEG_FRAME,
                false),
      explosion(this->texture_mgr) {
    switch (id) {
        case Worm::WeaponID::WBazooka:
            this->animation = GUI::Animation(this->texture_mgr.get(GUI::GameTextures::Missile),
                                             true, MISSILE_0_DEG_FRAME, false);
            break;
        case Worm::WeaponID::WGrenade:
            this->animation = GUI::Animation(this->texture_mgr.get(GUI::GameTextures::Grenade),
                                             false, MISSILE_0_DEG_FRAME, false);
            break;
        case Worm::WeaponID::WCluster:
            this->animation = GUI::Animation(this->texture_mgr.get(GUI::GameTextures::Cluster),
                                             false, MISSILE_0_DEG_FRAME, false);
            break;
        case Worm::WeaponID::WMortar:
            this->animation = GUI::Animation(this->texture_mgr.get(GUI::GameTextures::Mortar),
                                             false, MISSILE_0_DEG_FRAME, false);
            break;
        case Worm::WeaponID::WBanana:
            this->animation = GUI::Animation(this->texture_mgr.get(GUI::GameTextures::Banana),
                                             false, MISSILE_0_DEG_FRAME, false);
            break;
        case Worm::WeaponID::WHoly:
            this->animation = GUI::Animation(this->texture_mgr.get(GUI::GameTextures::Holy), false,
                                             MISSILE_0_DEG_FRAME, false);
            break;
        case Worm::WeaponID::WExplode:
            break;
        case Worm::WeaponID::WFragment:
            this->animation = GUI::Animation(this->texture_mgr.get(GUI::GameTextures::Fragment), false,
                                             0, true);
            this->updateManually = false;
            break;
        case Worm::WeaponID::WNone:
            break;
    }
    this->wid = id;
}

void Ammo::Bullet::update(float dt) {
    if (!this->explode) {
        if (this->updateManually) {
            float angle = (this->angle - 90);
            if (angle >= 360) {
                angle -= 360;
            }
            float angleStep = MISSILE_ANGLE_STEP;
            if (this->wid == Worm::WeaponID::WFragment) {
                angleStep = 60.0f;
            }
            this->animation.setFrame((int)std::floor(angle / angleStep));
        } else {
            this->animation.update(dt);
        }
    } else {
        this->explosion.update(dt);
    }
}

void Ammo::Bullet::render(GUI::Position p, GUI::Camera &cam) {
    //    if (this->direction == Direction::left) {
    //        this->animation.setFlip(SDL_FLIP_NONE);
    //    } else {
    //        this->animation.setFlip(SDL_FLIP_HORIZONTAL);
    //    }
    if (!this->explode) {
        this->animation.render(p, cam, SDL_FLIP_HORIZONTAL);
    } else {
        this->explosion.render(cam);
        //        this->explode = !this->explosion.finished();
    }
}

void Ammo::Bullet::setAngle(float angle) {
    this->angle = angle;
}

bool Ammo::Bullet::exploded() {
    return this->explosion.finished();
}

void Ammo::Bullet::madeImpact() {
    this->explode = true;
}

void Ammo::Bullet::setPosition(GUI::Position p) {
    this->position = p;
    this->explosion.position = p;
}

bool Ammo::Bullet::exploding() {
    return this->explode;
}

GUI::Position Ammo::Bullet::getPosition() {
    return this->position;
}
