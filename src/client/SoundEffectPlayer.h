//
// Created by rodrigo on 5/06/18.
//

#ifndef INC_4_WORMS_SOUNDEFFECTPLAYER_H
#define INC_4_WORMS_SOUNDEFFECTPLAYER_H

#include <SDL2/SDL.h>

#include "SoundEffect.h"

namespace GUI {
class SoundEffectPlayer {
   public:
    bool loop{false};

    SoundEffectPlayer(const GUI::SoundEffect &soundEffect);
    SoundEffectPlayer(const SoundEffect &soundEffect, float duration);
    SoundEffectPlayer(const GUI::SoundEffect &soundEffect, bool autoUpdate);
    ~SoundEffectPlayer();
    void update(float dt);
    void play();

   private:
    const SoundEffect *soundEffect;
    float duration{0.0f};
    float timeElapsed{0.0f};
    bool autoUpdate{false};
};
}

#endif  // INC_4_WORMS_SOUNDEFFECTPLAYER_H
