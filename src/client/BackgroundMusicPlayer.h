//
// Created by rodrigo on 25/06/18.
//

#ifndef INC_4_WORMS_BACKGROUNDMUSICPLAYER_H
#define INC_4_WORMS_BACKGROUNDMUSICPLAYER_H


#include <SDL2/SDL.h>

#include "BackgroundMusic.h"

namespace GUI {
    class BackgroundMusicPlayer {
    public:
        bool loop{false};

        explicit BackgroundMusicPlayer(const GUI::BackgroundMusic &backgroundMusic);
        ~BackgroundMusicPlayer();
        void play();

    private:
        const BackgroundMusic *backgroundMusic;
    };
}


#endif //INC_4_WORMS_BACKGROUNDMUSICPLAYER_H
