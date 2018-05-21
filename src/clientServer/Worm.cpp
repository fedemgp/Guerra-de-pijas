/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <SDL2/SDL_system.h>
#include <iostream>

#include "GameStateMsg.h"
#include "Worm.h"
#include "WormStartJump.h"
#include "WormStill.h"
#include "WormWalk.h"
#include "WormBackFlip.h"
#include "WormJumping.h"
#include "WormEndJump.h"
#include "WormBackFlipping.h"
#include "WormEndBackFlip.h"

Worm::Worm::Worm(const GUI::GameTextureManager &texture_mgr)
    : texture_mgr(texture_mgr), animation(texture_mgr.get(GUI::GameTextures::WormIdle)) {
    this->setState(::Worm::StateID::Still);
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
        case SDLK_RETURN:
            i = this->state->jump(*this);
            if (i != IO::PlayerInput::moveNone)
                *out << i;
            break;
        case SDLK_BACKSPACE:
            i = this->state->backFlip(*this);
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
    if (this->direction == Direction::left) {
        this->animation.setFlip(SDL_FLIP_NONE);
    } else {
        this->animation.setFlip(SDL_FLIP_HORIZONTAL);
    }

    this->animation.render(renderer, x, y);
}

void Worm::Worm::update(float dt) {
    this->state->update(dt);
    this->animation.update(dt);
}

GUI::Animation Worm::Worm::getAnimation(StateID state) const {
    switch (state) {
        case StateID::Still:
            return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::WormIdle), true};
        case StateID::Walk:
            return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::WormWalk)};
        case StateID::StartBackFlip:
        case StateID::StartJump:
            return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::StartJump), true};
        case StateID::Jumping:
            return GUI::Animation {this->texture_mgr.get(GUI::GameTextures::Jumping)};
        case StateID::EndBackFlip:
        case StateID::EndJump:
            return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::EndJump), true};
        case StateID::BackFlipping: {
            GUI::Animation animation{this->texture_mgr.get(GUI::GameTextures::BackFlipping)};
            animation.setAnimateOnce();
            return animation;
        }
    }
    return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::WormIdle)};
}

void Worm::Worm::setState(StateID state) {
    if (this->state == nullptr || this->state->getState() != state) {
        this->animation = this->getAnimation(state);

        /* creates the right state type */
        switch (state) {
            case StateID::Still:
                this->state = std::shared_ptr<State>(new Still());
                break;
            case StateID::Walk:
                this->state = std::shared_ptr<State>(new Walk());
                break;
            case StateID::StartJump:
                this->state = std::shared_ptr<State>(new StartJump());
                break;
            case StateID::Jumping:
                this->state = std::shared_ptr<State>(new Jumping());
                break;
            case StateID::EndJump:
                this->state = std::shared_ptr<State>(new EndJump());
                break;
            case StateID::StartBackFlip:
                this->state = std::shared_ptr<State>(new BackFlip());
                break;
            case StateID::BackFlipping:
                this->state = std::shared_ptr<State>(new BackFlipping());
                break;
            case StateID::EndBackFlip:
                this->state = std::shared_ptr<State>(new EndBackFlip());
                break;
        }
    }
}
