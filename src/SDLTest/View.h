/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 12/05/18
 */

#ifndef __View_H__
#define __View_H__

#include <SDL2/SDL.h>
#include <string>
#include "Texture.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define WORM_WALK_SPRITES_QUANTITY 15

class View{
public:
    SDL_Window *window;
    SDL_Surface *screenSurface;
    SDL_Renderer *renderer;
    Texture fooTexture;
    SDL_Rect spriteClips[WORM_WALK_SPRITES_QUANTITY];
    void close();
    View();
    ~View();
    void loadMedia();

private:
    bool SDLInitiated;
    bool IMGInitiated;
};


#endif //__View_H__
