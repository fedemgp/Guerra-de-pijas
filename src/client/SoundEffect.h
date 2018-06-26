//
// Created by rodrigo on 4/06/18.
//

#ifndef INC_4_WORMS_SOUNDEFFECT_H
#define INC_4_WORMS_SOUNDEFFECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

namespace GUI {
class SoundEffect {
   public:
    SoundEffect(const std::string &filename);
    SoundEffect(SoundEffect &&other);
    ~SoundEffect();
    Mix_Chunk *getChunk() const;
    void play(bool loop) const;

   private:
    Mix_Chunk *soundEffect{nullptr};
};
}

#endif  // INC_4_WORMS_SOUNDEFFECT_H
