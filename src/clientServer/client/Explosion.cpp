//
// Created by rodrigo on 2/06/18.
//

#include "Explosion.h"


Worm::Explosion::Explosion(const GUI::GameTextureManager &texture_mgr)
        : texture_mgr(texture_mgr) {
    this->animations.emplace_back(this->texture_mgr.get(GUI::GameTextures::Explosion));
    this->animations.back().setAnimateOnce();
//    this->animations.emplace_back(this->texture_mgr.get(GUI::GameTextures::Flame));
//    this->animations.emplace_back(this->texture_mgr.get(GUI::GameTextures::Smoke));
}

void Worm::Explosion::update(float dt) {
    for (auto &animation : this->animations) {
        animation.update(dt);
        this->explosionFinished = animation.finished();
    }
}

void Worm::Explosion::render(GUI::Camera &cam) {
    for (auto &animation : this->animations) {
        animation.render(this->position, cam, SDL_FLIP_HORIZONTAL);
    }
}

bool Worm::Explosion::finished() {
    return this->explosionFinished;
}