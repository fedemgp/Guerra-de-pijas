/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 27/05/18
 */

#include "GameStateMsg.h"
#include "Weapon.h"

Worm::Weapon::Weapon(const GUI::GameTextureManager &tex): textureMgr(tex){
//    this->animations.emplace_back(this->textureMgr.get(GUI::GameTextures::WormIdle), true);
}

void Worm::Weapon::update(float dt){
    for (auto &animation : this->animations){
        animation.update(dt);
    }
}

void Worm::Weapon::render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip){
    for (auto &animation : this->animations){
        animation.render(p, cam, flip);
    }
}

void Worm::Weapon::setWeapon(WeaponID &id){
    if (id != this->current){
        // Clean previous animation
        this->current = id;
        this->animations.erase(this->animations.begin(), this->animations.end());
        switch (id){
            case WeaponID::WBazooka:
                this->animations.emplace_back(this->textureMgr.get(GUI::GameTextures::Aim), true,
                                              BAZOOKA_CENTER_FRAME, false);
                break;
            case WeaponID::WNone:
                break;
        }
    }
}

const Worm::WeaponID &Worm::Weapon::getWeaponID() const{
    return this->current;
}

