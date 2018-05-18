/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include <string>

#include "Animation.h"

GUI::Animation::Animation(const std::string &filename, SDL_Renderer &renderer, GUI::Color key) {
    /* loads the image into a temporary surface */
    SDL_Surface *tmp = IMG_Load(filename.c_str());
    if (!tmp) {
        throw Exception{"Error loading %s: %s", filename.c_str(), IMG_GetError()};
    }

    SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, key.r, key.g, key.b));

    /* creates a texture from the surface */
    this->texture = SDL_CreateTextureFromSurface(&renderer, tmp);
    if (!this->texture) {
        SDL_FreeSurface(tmp);
        throw Exception{"Error creating texture for %s: %s", filename.c_str(), SDL_GetError()};
    }

    /* assumes the frames are squares */
    this->numFrames = tmp->h / tmp->w;
    this->size = tmp->w;

    /* releases the temporary surface */
    SDL_FreeSurface(tmp);

    assert(this->numFrames > 0);
    assert(this->size > 0);
}

GUI::Animation::~Animation() {
    if (!this->texture) {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }
}

void GUI::Animation::update(float dt) {
    this->elapsed += dt;

    /* checks if the frame should be updated based on the time elapsed since the last update */
    while (this->elapsed > this->frameRate) {
        this->advanceFrame();
        this->elapsed -= this->frameRate;
    }
}

void GUI::Animation::render(SDL_Renderer &renderer, int x, int y) {
    /* set rendering space and render to screen */
    SDL_Rect clip = {0, this->size * this->currentFrame, this->size, this->size};
    SDL_Rect dst = {x, y, this->size, this->size};
    SDL_RenderCopyEx(&renderer, this->texture, &clip, &dst, 0, nullptr, this->flipType);
}

void GUI::Animation::advanceFrame() {
    this->currentFrame = (this->currentFrame + 1) % this->numFrames;
}

void GUI::Animation::flip(SDL_RendererFlip flip_type) {
    this->flipType = flip_type;
}