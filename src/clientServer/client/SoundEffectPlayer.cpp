//
// Created by rodrigo on 5/06/18.
//

#include "SoundEffectPlayer.h"

GUI::SoundEffectPlayer::SoundEffectPlayer(const GUI::SoundEffect &soundEffect, float duration)
    : soundEffect(&soundEffect),
      duration(duration) {
//    this->soundEffect->play();
}

GUI::SoundEffectPlayer::SoundEffectPlayer(const GUI::SoundEffect &soundEffect)
        : soundEffect(&soundEffect) {}

GUI::SoundEffectPlayer::~SoundEffectPlayer() {}

void GUI::SoundEffectPlayer::update(float dt) {
    this->timeElapsed += dt;
    if (this->timeElapsed > this->duration) {
        this->play();
        this->timeElapsed = 0.0f;
    }
}

void GUI::SoundEffectPlayer::play() {
    this->soundEffect->play();
}
