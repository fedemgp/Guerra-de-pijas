//
// Created by rodrigo on 4/06/18.
//

#ifndef INC_4_WORMS_GAMESOUNDEFFECTS_H
#define INC_4_WORMS_GAMESOUNDEFFECTS_H

#include "SoundEffectManager.h"
#include "utils.h"

namespace GUI {
/** Different kinds of sound effects. */
enum class GameSoundEffects {
    WalkCompress,
    Explosion,
    WormLanding,
    WormDrowning,
    Splash,
    WormJump,
    WormBackFlip,
    WormHit,
    WormDie,
    Holy,
    AirStrike,
    Teleport,
    Shot,
    Banana
};

/** Specialized SoundEffectManager class. */
using GameSoundEffectManager = SoundEffectManager<GameSoundEffects, Utils::EnumClassHash>;
}  // namespace GUI

#endif  // INC_4_WORMS_GAMESOUNDEFFECTS_H
