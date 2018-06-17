/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "Animation.h"
#include "Texture.h"

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

GUI::Animation::Animation(const GUI::Texture &texture, bool playReversed, int initialFrame,
                          bool autoUpdate)
    : Animation(texture, playReversed) {
    assert(this->numFrames > initialFrame);
    this->currentFrame = initialFrame;
    this->autoUpdate = autoUpdate;
}

GUI::Animation::~Animation() {}

void GUI::Animation::update(float dt) {
    if (this->autoUpdate) {
        this->elapsed += dt;
        /* checks if the frame should be updated based on the time elapsed since the last update */
        while (this->elapsed > this->frameRate) {
            this->advanceFrame();
            this->elapsed -= this->frameRate;
        }
    }
}

/**
 * @brief Renders the animation in the given coordinates.
 *
 * @param renderer Renderer.
 * @param x X coordinate.
 * @param y Y corrdinate.
 */
void GUI::Animation::render(Position &p, Camera &cam, const SDL_RendererFlip &flipType) {
    this->setFlip(flipType);
    SDL_Rect clip = {0, this->size * this->currentFrame, this->size, this->size};
    cam.draw(*this->texture, p, clip, this->flipType);
}

/**
 * @brief Resets the animation.
 *
 */
void GUI::Animation::reset() {
    this->currentFrame = 0;
}

void GUI::Animation::advanceFrame() {
    if (!this->playInverse) {
        if (this->playReversed) {
            if (this->currentFrame == 0 && this->step < 0) {
                this->step = 1;
            } else if (this->currentFrame == this->numFrames - 1 && this->step > 0) {
                this->step = -1;
            }
        }

        if (this->playOnce &&
            this->currentFrame == this->numFrames - 1) {  // Por ahora ignora el playReversed
            this->animationFinished = true;
        }

        if (!this->animationFinished) {
            this->currentFrame = (this->currentFrame + this->step) % this->numFrames;
        }
    } else {
        if (this->currentFrame == 0) {
            this->animationFinished = true;
        } else {
            this->currentFrame -= 1;
        }
    }
}

void GUI::Animation::setFlip(SDL_RendererFlip flip_type) {
    this->flipType = flip_type;
}

SDL_RendererFlip GUI::Animation::getFlip() {
    return this->flipType;
}

void GUI::Animation::setFrame(int frame) {
    assert(frame < this->numFrames);
    assert(frame >= 0);
    this->currentFrame = frame;
}

void GUI::Animation::setAnimateOnce() {
    this->playOnce = true;
}

bool GUI::Animation::finished() {
    return this->animationFinished;
}

void GUI::Animation::setAutoUpdate(bool autoUpdate) {
    this->autoUpdate = autoUpdate;
}

void GUI::Animation::setPlayInverse() {
    this->playInverse = true;
    this->currentFrame = this->numFrames - 1;
}
