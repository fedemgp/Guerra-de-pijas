/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 12/05/18
 */

#include <Exception.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "View.h"

View::View() : window(nullptr), screenSurface(nullptr), renderer(nullptr),
               fooTexture(), SDLInitiated(false),
               IMGInitiated(false){
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        throw Exception("SDL could not initialize! SDL_Error: %s",
                        SDL_GetError());
    }
    this->SDLInitiated = true;

    //Create window
    this->window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                    SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (this->window == nullptr){
        this->close();
        throw Exception("Window could not be created! SDL_Error: %s",
                        SDL_GetError());
    }

    //Create renderer for window
    this->renderer = SDL_CreateRenderer(this->window, -1,
                                        SDL_RENDERER_ACCELERATED |
                                        SDL_RENDERER_PRESENTVSYNC);
    if (this->renderer == nullptr){
        this->close();
        throw Exception("Renderer could not be created! SDL Error:%s",
                        SDL_GetError());
    }

    //Initialize PGN loading
    int imgFlags = IMG_INIT_PNG;
    if ((!IMG_Init(imgFlags)) & imgFlags){
        this->close();
        throw Exception("SDL_image could not initialize! SDL_image Error: %s",
                        IMG_GetError());
    }
    this->IMGInitiated = true;
}

View::~View(){
    this->close();
}

void View::loadMedia(){
}

void View::close(){
    if (this->renderer != nullptr){
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }

    if (this->window != nullptr){
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }

    //Quit SDL subsystems
    if (this->IMGInitiated){
        IMG_Quit();
    }
    if (this->SDLInitiated){
        SDL_Quit();
    }
}