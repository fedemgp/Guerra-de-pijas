#ifndef GAME_TEXTURES_H_
#define GAME_TEXTURES_H_

#include "TextureManager.h"
#include "utils.h"

namespace GUI {
/** Different kinds of textures. */
enum class GameTextures { WormWalk, WormIdle, LongGirder, ShortGirder, StartJump, Jumping,
    EndJump, BackFlipping, Aim
};

/** Specialized TextureManager class. */
using GameTextureManager = TextureManager<GameTextures, Utils::EnumClassHash>;
}  // namespace GUI

#endif
