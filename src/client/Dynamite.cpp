/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 16/06/18
 */

#include "Dynamite.h"

Worm::Dynamite::Dynamite(const GUI::GameTextureManager &tex) :
        Weapon(tex, GUI::GameTextures::WormDynamite, DYNAMITE_CENTER_FRAME,
               WeaponID::WDynamite){

}

void Worm::Dynamite::update(float dt){
    this->weaponAnimation.update(dt);
}

void Worm::Dynamite::render(GUI::Position &p, GUI::Camera &cam,
                            SDL_RendererFlip &flip){
    this->weaponAnimation.render(p, cam, flip);
}

void Worm::Dynamite::setAngle(float angle, Worm::Direction d){}

void Worm::Dynamite::startShot(){}

void Worm::Dynamite::endShot(){}

bool Worm::Dynamite::positionSelected(){
    return false;
}


