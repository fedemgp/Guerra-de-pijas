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
    SoundEffectPlayer(const SoundEffect &soundEffect);
    ~SoundEffectPlayer();

   private:
    const SoundEffect *soundEffect;
};
}

#endif  // INC_4_WORMS_SOUNDEFFECTPLAYER_H
