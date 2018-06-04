/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#include "PowerBar.h"
#include "Weapon.h"

Weapon::PowerBar::PowerBar(const GUI::GameTextureManager &tex): textureManager(tex){
    this->animations.reserve(POWER_FRAMES_QUANTITY);
}

void Weapon::PowerBar::setAngle(float angle, Worm::Direction d){
    this->angle = d == Worm::Direction::right ? angle : 180 - angle;
}

void Weapon::PowerBar::update(float dt){
    if (this->power < POWER_FRAMES_QUANTITY){
        this->animations.emplace_back(this->textureManager.get(GUI::GameTextures::PowerBar), false, this->power ,false);
        this->power++;
    } else {
        this->animations.erase(this->animations.begin(), this->animations.end());
        this->power = 0;
    }
}

void Weapon::PowerBar::render(GUI::Position &p, GUI::Camera &cam,
                              SDL_RendererFlip &flip){
    for (int i = 0; i < this->power; i++){
        GUI::Position powerPos =
                GUI::Position((SCOPE_DISTANCE * (log10(10 * i/17))) * cos(this->angle * PI / 180),
                              (SCOPE_DISTANCE * (log10(10 * i/17)))* sin(this->angle * PI / 180)) + p;
        this->animations[i].render(powerPos, cam, flip);
    }

}
