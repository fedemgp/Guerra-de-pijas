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
    SoundEffectPlayer(const SoundEffect &soundEffect, float duration);
    SoundEffectPlayer(const SoundEffect &soundEffect);
    ~SoundEffectPlayer();
    void update(float dt);
    void play();

   private:
    const SoundEffect *soundEffect;
    float duration{0.0f};
    float timeElapsed{0.0f};
};
}

#endif  // INC_4_WORMS_SOUNDEFFECTPLAYER_H
