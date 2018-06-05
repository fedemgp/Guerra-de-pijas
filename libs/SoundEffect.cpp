//
// Created by rodrigo on 4/06/18.
//

#include "SoundEffect.h"
#include "Exception.h"

GUI::SoundEffect::SoundEffect(const std::string &filename) {
    this->soundEffect = Mix_LoadWAV(filename.c_str());
    if (!this->soundEffect) {
        throw Exception{"Error loading %s: %s", filename.c_str(), Mix_GetError()};
    }
}

GUI::SoundEffect::~SoundEffect() {
//    if (this->soundEffect != nullptr) {
//        Mix_FreeChunk(this->soundEffect);
//        this->soundEffect = nullptr;
//    }
}

Mix_Chunk *GUI::SoundEffect::getChunk() const {
    return this->soundEffect;
}
