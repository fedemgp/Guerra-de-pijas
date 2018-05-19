/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <SDL2/SDL_system.h>

#include "GameStateMsg.h"
#include "Worm.h"
#include "WormStill.h"
#include "WormWalk.h"

Worm::Worm::Worm(const TextureManager &texture_mgr) : texture_mgr(texture_mgr) {
    this->setState(::Worm::StateID::still);
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

void Worm::Worm::render(int x, int y, SDL_Renderer &renderer) {
    this->state->render(x, y, renderer);
}

void Worm::Worm::update(float dt) {
    this->state->update(dt);
}

GUI::Animation Worm::Worm::getAnimation(::Worm::StateID state) const {
    return GUI::Animation{this->texture_mgr.get(state)};
}

void Worm::Worm::setState(StateID state) {
    /* creates the right state type */
    switch (state) {
        case StateID::still:
            this->state = std::shared_ptr<State>(new Still{this->getAnimation(state)});
            break;
        case StateID::walk:
            this->state = std::shared_ptr<State>(new Walk{this->getAnimation(state)});
            break;
    }
}
