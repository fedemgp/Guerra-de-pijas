/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <SDL2/SDL_system.h>

#include "GameStateMsg.h"
#include "Worm.h"
#include "WormQuiet.h"

Worm::Worm::Worm(SDL_Renderer &renderer) : renderer(renderer) {
    this->state = std::shared_ptr<State>(new Quiet(this->renderer, SDL_FLIP_NONE));
}

void Worm::Worm::handleKeyDown(SDL_Keycode key, IO::Stream<IO::PlayerInput> *out) {
    IO::PlayerInput i;
    switch (key) {
        case SDLK_RIGHT:
            i = this->state->moveRight(*this);
            if (i != IO::PlayerInput::moveNone)
                *out << i;
            break;
        case SDLK_LEFT:
            i = this->state->moveLeft(*this);
            if (i != IO::PlayerInput::moveNone)
                *out << i;
            break;
    }
}

void Worm::Worm::handleKeyUp(SDL_Keycode key, IO::Stream<IO::PlayerInput> *out) {
    IO::PlayerInput i;
    switch (key) {
        case SDLK_RIGHT:
            i = this->state->stopMove(*this);
            if (i != IO::PlayerInput::moveNone)
                *out << i;
            break;
        case SDLK_LEFT:
            i = this->state->stopMove(*this);
            if (i != IO::PlayerInput::moveNone)
                *out << i;
            break;
    }
}

void Worm::Worm::render(int x, int y) {
    this->state->render(x, y);
}

void Worm::Worm::update(double dt) {
    this->state->update(dt);
}