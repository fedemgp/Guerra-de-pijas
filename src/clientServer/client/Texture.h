#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL2/SDL.h>
#include <string>
#include "Color.h"

namespace GUI {
class Texture {
   public:
    Texture(const std::string &filename, SDL_Renderer &renderer, Color key);
    Texture(Texture &&other);
    ~Texture();

    int getWidth() const;
    int getHeight() const;

    void render(SDL_Renderer &renderer, SDL_Rect clip, SDL_Rect dst, SDL_RendererFlip flip) const;
    void render(SDL_Renderer &renderer, SDL_Rect dst) const;

   private:
    int height{0}, width{0};
    SDL_Texture *texture{nullptr};
};
}  // namespace GUI

#endif
