#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL2/SDL.h>
#include <string>
#include "Color.h"

namespace GUI {
class Texture {
   public:
    Texture(const std::string &filename, SDL_Renderer &renderer, Color key);
    Texture(SDL_Texture *texture, int width, int height);
    Texture(Texture &&other);
    ~Texture();

    int getWidth() const;
    int getHeight() const;
    SDL_Texture *get() const;

   private:
    int height{0}, width{0};
    SDL_Texture *texture{nullptr};
};
}  // namespace GUI

#endif
