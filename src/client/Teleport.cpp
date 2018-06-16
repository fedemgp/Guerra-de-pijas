//
// Created by rodrigo on 16/06/18.
//

#include "Teleport.h"

Worm::Teleport::Teleport(const GUI::GameTextureManager &tex)
        : Weapon(tex, GUI::GameTextures::WormTeleport, TELEPORT_CENTER_FRAME,
                 WeaponID::WTeleport){
    this->weaponAnimation.setAnimateOnce();
}

void Worm::Teleport::update(float dt){
    if (!this->weaponAnimation.finished()){
        this->weaponAnimation.update(dt);
    } else{
        this->endAnimation();
    }
}

void Worm::Teleport::render(GUI::Position &p, GUI::Camera &cam,
                                SDL_RendererFlip &flip){
    this->weaponAnimation.render(p, cam, flip);
}

void Worm::Teleport::setAngle(float angle, Worm::Direction d){

}

void Worm::Teleport::startShot(){}

void Worm::Teleport::endShot(){}

bool Worm::Teleport::positionSelected(){
    this->weaponAnimation.setAutoUpdate(true);
    return true;
}

void Worm::Teleport::endAnimation(){
    this->weaponAnimation.setFrame(TELEPORT_CENTER_FRAME);
    this->weaponAnimation.setAutoUpdate(false);
}
