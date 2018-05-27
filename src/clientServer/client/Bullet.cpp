/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#include <cmath>
#include <iostream>
#include "Bullet.h"

Ammo::Bullet::Bullet(const GUI::GameTextureManager &texture_mgr):
        texture_mgr(texture_mgr),
        animation(this->texture_mgr.get(GUI::GameTextures::Missile), true, MISSILE_0_DEG_FRAME, false){}

void Ammo::Bullet::update(float dt){
    this->animation.update(dt);
}

void Ammo::Bullet::render(int x, int y, SDL_Renderer &renderer){
//    if (this->direction == Direction::left) {
//        this->animation.setFlip(SDL_FLIP_NONE);
//    } else {
//        this->animation.setFlip(SDL_FLIP_HORIZONTAL);
//    }
    this->animation.setFlip(SDL_FLIP_HORIZONTAL);
    this->animation.render(renderer, x, y);
}

void Ammo::Bullet::setAngle(float angle) {//std::cout<<"bullet angle "<<angle<<std::endl;
    this->animation.setFrame((int) std::floor((angle - 90) / MISSILE_ANGLE_STEP));
}
