//
// Created by rodrigo on 25/06/18.
//

#include "BackgroundMusic.h"
#include "Exception.h"

GUI::BackgroundMusic::BackgroundMusic(const std::string &filename) {
    this->backgroundMusic = Mix_LoadMUS(filename.c_str());
    if (!this->backgroundMusic) {
        throw Exception{"Error loading %s: %s", filename.c_str(), Mix_GetError()};
    }
}

GUI::BackgroundMusic::~BackgroundMusic() {
    if (this->backgroundMusic != nullptr) {
        Mix_FreeMusic(this->backgroundMusic);
    }
}

Mix_Music *GUI::BackgroundMusic::getMusic() const {
    return this->backgroundMusic;
}

GUI::BackgroundMusic::BackgroundMusic(GUI::BackgroundMusic &&other) {
    std::swap(this->backgroundMusic, other.backgroundMusic);
}

void GUI::BackgroundMusic::play() const {
    Mix_PlayMusic(this->backgroundMusic, -1);
}
