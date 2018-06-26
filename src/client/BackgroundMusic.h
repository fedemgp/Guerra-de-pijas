//
// Created by rodrigo on 25/06/18.
//

#ifndef INC_4_WORMS_BACKGROUNDMUSIC_H
#define INC_4_WORMS_BACKGROUNDMUSIC_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

namespace GUI {
    class BackgroundMusic {
    public:
        BackgroundMusic(const std::string &filename);
        BackgroundMusic(BackgroundMusic &&other);
        ~BackgroundMusic();
        Mix_Music *getMusic() const;
        void play() const;

    private:
        Mix_Music *backgroundMusic{nullptr};
    };
}


#endif //INC_4_WORMS_BACKGROUNDMUSIC_H
