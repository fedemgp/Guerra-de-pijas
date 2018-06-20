/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "Exception.h"
#include "Window.h"

GUI::Window::Window() : Window(WINDOW_WIDTH, WINDOW_HEIGHT) {}

GUI::Window::Window(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        throw Exception{"SDL could not initialize: %s", SDL_GetError()};
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
    }

    this->window = SDL_CreateWindow("Worms", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

    SDL_SetWindowSize(this->window, width, height);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        throw Exception("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

GUI::Window::~Window() {
    this->close();
}

/**
 * @brief Maximizes the window.
 *
 */
void GUI::Window::maximize() {
    SDL_MaximizeWindow(this->window);
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

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void GUI::Window::clear() {
    this->clear({0xFF, 0xFF, 0xFF, 0xFF});
}

void GUI::Window::clear(SDL_Color color) {
    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(this->renderer);
}

void GUI::Window::render() {
    SDL_RenderPresent(this->renderer);
}

SDL_Renderer& GUI::Window::getRenderer() {
    return *this->renderer;
}

/**
 * @brief Gets the window's height.
 *
 * @return int Window height.
 */
int GUI::Window::getHeight() const {
    int h, w;
    SDL_GL_GetDrawableSize(this->window, &w, &h);
    return h;
}

/**
 * @brief Gets the window's width.
 *
 * @return int Window width.
 */
int GUI::Window::getWidth() const {
    int h, w;
    SDL_GL_GetDrawableSize(this->window, &w, &h);
    return w;
}

/**
 * @brief Checks if the mouse cursor is contained in this window.
 *
 * @return true is the mouse is in the current window.
 */
bool GUI::Window::containsMouse() const {
    return (SDL_GetMouseFocus() == this->window);
}
