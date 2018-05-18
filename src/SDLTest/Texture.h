/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 12/05/18
 */

#ifndef __Texture_H__
#define __Texture_H__

#include <SDL2/SDL_image.h>

class Texture {
   public:
    // Initializes variables
    Texture();
    // Deallocates memory
    ~Texture();
    // Loads image at specified path
    void loadFromFile(const char *path, SDL_Renderer *renderer, Uint8 r = 0x00, Uint8 g = 0x00,
                      Uint8 b = 0x00);
    // Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    // Set blending
    void setBlendMode(SDL_BlendMode blending);
    // Set alpha modulation
    void setAlpha(Uint8 alpha);
    // Renders texture at given point
    void render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clip = nullptr, double angle = 0.0,
                SDL_Point *center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    // Gets image dimensions
    int getWidth();
    int getHeight();
    // Deallocates texture
    void free();

   private:
    // The actual hardware texture
    SDL_Texture *texture;
    // Image dimensions
    int width;
    int height;
};

#endif  //__Texture_H__
