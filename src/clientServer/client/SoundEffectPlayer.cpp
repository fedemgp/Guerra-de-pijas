//
// Created by rodrigo on 5/06/18.
//

#include "SoundEffectPlayer.h"

GUI::SoundEffectPlayer::SoundEffectPlayer(const GUI::SoundEffect &soundEffect)
    : soundEffect(&soundEffect) {
    Mix_PlayChannel(-1, this->soundEffect->getChunk(), 0);
}

GUI::SoundEffectPlayer::~SoundEffectPlayer() {}
