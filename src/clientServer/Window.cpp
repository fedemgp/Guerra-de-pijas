/*
 * Created by Federico Manuel Gomez Peter 
 * Date: 17/05/18.
 */

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Exception.h"
#include "Window.h"

GUI::Window::Window(): Window(WINDOW_WIDTH, WINDOW_HEIGHT){}

GUI::Window::Window(int width, int height): width(width), height(height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw Exception{"SDL could not initialize: %s", SDL_GetError()};
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    this->window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!this->window) {
        //TODO call SDL_GETError
        throw Exception{"Failed creating the window"};
    }

    this->surface = SDL_GetWindowSurface(this->window);
    if (!this->surface) {
        //TODO call SDL_GETError
        throw Exception{"Failed creating the screen surface"};
    }

    this->renderer = SDL_CreateRenderer(this->window, -1,
                                        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!this->renderer) {
        //TODO call SDL_GETError
        throw Exception{"Failed creating the screen surface"};
    }

    if ((!IMG_Init(IMG_INIT_PNG)) & IMG_INIT_PNG) {
        throw Exception{"Failed initialiing IMG: %s", IMG_GetError()};
    }
}

GUI::Window::~Window() {
    if (this->renderer != nullptr){
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }

    if (this->window != nullptr){
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
    IMG_Quit();
    SDL_Quit();
}

void GUI::Window::clear() {
    SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(this->renderer);
}

void GUI::Window::render() {
    SDL_RenderPresent(this->renderer);
}

SDL_Renderer& GUI::Window::get_renderer() {
    return *this->renderer;
}