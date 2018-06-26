//
// Created by rodrigo on 25/06/18.
//

#ifndef INC_4_WORMS_GAMEBACKGROUNDMUSIC_H
#define INC_4_WORMS_GAMEBACKGROUNDMUSIC_H

#include "BackgroundMusicManager.h"
#include "utils.h"

namespace GUI {
/** Different kinds of background music. */
    enum class GameBackgroundMusic {
        Original,
        MurderTrain
    };

/** Specialized BackgroundMusicManager class. */
    using GameBackgroundMusicManager = BackgroundMusicManager<GameBackgroundMusic, Utils::EnumClassHash>;
}  // namespace GUI

#endif //INC_4_WORMS_GAMEBACKGROUNDMUSIC_H
