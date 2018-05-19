/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <cassert>
#include <string>

#include "Animation.h"

GUI::Animation::Animation(const Texture &texture) : texture(&texture) {
    /* assumes the frames are squares */
    this->numFrames = this->texture->getHeight() / this->texture->getWidth();
    this->size = this->texture->getWidth();

    assert(this->numFrames > 0);
    assert(this->size > 0);
}

GUI::Animation::Animation(const Texture &texture, bool playReversed) : Animation(texture) {
    this->playReversed = playReversed;
}

GUI::Animation::~Animation() {}

void GUI::Animation::update(float dt) {
    this->elapsed += dt;

    /* checks if the frame should be updated based on the time elapsed since the last update */
    while (this->elapsed > this->frameRate) {
        this->advanceFrame();
        this->elapsed -= this->frameRate;
    }
}

/**
 * @brief Renders the animation in the given coordinates.
 *
 * @param renderer Renderer.
 * @param x X coordinate.
 * @param y Y corrdinate.
 */
void GUI::Animation::render(SDL_Renderer &renderer, int x, int y) {
    SDL_Rect clip = {0, this->size * this->currentFrame, this->size, this->size};
    SDL_Rect dst = {x, y, this->size, this->size};
    this->texture->render(renderer, clip, dst, this->flipType);
}

/**
 * @brief Resets the animation.
 *
 */
void GUI::Animation::reset() {
    this->currentFrame = 0;
}

void GUI::Animation::advanceFrame() {
    if (this->playReversed) {
        if (this->currentFrame == 0 && this->step < 0) {
            this->step = 1;
        } else if (this->currentFrame == this->numFrames - 1 && this->step > 0) {
            this->step = -1;
        }
    }
    this->currentFrame = (this->currentFrame + this->step) % this->numFrames;
}

void GUI::Animation::setFlip(SDL_RendererFlip flip_type) {
    this->flipType = flip_type;
}

SDL_RendererFlip GUI::Animation::getFlip() {
    return this->flipType;
}
