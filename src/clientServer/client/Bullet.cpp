/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#include "Bullet.h"
#include <cmath>
#include <iostream>

Ammo::Bullet::Bullet(const GUI::GameTextureManager &texture_mgr)
    : texture_mgr(texture_mgr),
      animation(this->texture_mgr.get(GUI::GameTextures::Missile), true, MISSILE_0_DEG_FRAME,
                false),
      explosion(this->texture_mgr) {
}

void Ammo::Bullet::update(float dt) {
    if (!this->explode) {
        this->animation.update(dt);
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

void Ammo::Bullet::setAngle(float angle) {  // std::cout<<"bullet angle "<<angle<<std::endl;
    this->animation.setFrame((int)std::floor((angle - 90) / MISSILE_ANGLE_STEP));
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
