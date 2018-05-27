/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "Exception.h"
#include "Window.h"

GUI::Window::Window() : Window(WINDOW_WIDTH, WINDOW_HEIGHT) {}

GUI::Window::Window(int width, int height) : width(width), height(height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        throw Exception{"SDL could not initialize: %s", SDL_GetError()};
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    this->window = SDL_CreateWindow("Worms", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    width, height, SDL_WINDOW_SHOWN);
    if (!this->window) {
        this->close();
        throw Exception{"Window could not be created: %s", SDL_GetError()};
    }

    this->renderer =
        SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!this->renderer) {
        this->close();
        throw Exception{"Failed creating the render: %s", SDL_GetError()};
    }

    if ((!IMG_Init(IMG_INIT_PNG)) & IMG_INIT_PNG) {
        this->close();
        throw Exception{"Failed initialiing IMG: %s", IMG_GetError()};
    }

    if (TTF_Init() == -1) {
        this->close();
        throw Exception{"SDL_ttf could not initialize! SDL_ttf Error: %s", TTF_GetError()};
    }
}

GUI::Window::~Window() {
    this->close();
}

void GUI::Window::close() {
    if (this->renderer != nullptr) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }

    if (this->window != nullptr) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }

    TTF_Quit();
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

SDL_Renderer& GUI::Window::getRenderer() {
    return *this->renderer;
}
