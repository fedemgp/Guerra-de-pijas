/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <SDL2/SDL_system.h>
#include <cmath>

#include "GameStateMsg.h"
#include "Worm.h"
#include "WormBackFlip.h"
#include "WormBackFlipping.h"
#include "WormEndBackFlip.h"
#include "WormEndJump.h"
#include "WormJumping.h"
#include "WormStartJump.h"
#include "WormStill.h"
#include "WormWalk.h"

Worm::Worm::Worm(const GUI::GameTextureManager &texture_mgr)
    : texture_mgr(texture_mgr),
      animation(texture_mgr.get(GUI::GameTextures::WormIdle)),
      weapon(texture_mgr) {
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
        case SDLK_UP:
            i = this->state->pointUp(*this);
            if (i != IO::PlayerInput::moveNone)
                *out << i;
            break;
        case SDLK_DOWN:
            i = this->state->pointDown(*this);
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
        case SDLK_1:
            i = this->state->bazooka(*this);
            if (i != IO::PlayerInput::moveNone)
                *out << i;
            break;
        case SDLK_SPACE:
            i = this->state->startShot(*this);
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
        case SDLK_SPACE:
            i = this->state->endShot(*this);
            if (i != IO::PlayerInput::moveNone)
                *out << i;
            break;
    }
}

void Worm::Worm::render(GUI::Position &p, GUI::Camera &cam) {
    SDL_RendererFlip flipType =
        this->direction == Direction::left ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    if (this->state->getState() != StateID::Still ||
        this->weapon.getWeaponID() == WeaponID::WNone) {
        this->animation.render(p, cam, flipType);
    } else {
        this->weapon.render(p, cam, flipType);
    }
}

void Worm::Worm::update(float dt) {
    this->state->update(dt);
    this->animation.update(dt);
    this->weapon.update(dt);
}

GUI::Animation Worm::Worm::getAnimation(StateID state) const {
    switch (state) {
        case StateID::Still:
            break;
        case StateID::Walk:
            return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::WormWalk)};
        case StateID::StartBackFlip:
        case StateID::StartJump:
            return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::StartJump), true};
        case StateID::Jumping:
            return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::Jumping)};
        case StateID::EndBackFlip:
        case StateID::EndJump:
            return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::EndJump), true};
        case StateID::BackFlipping: {
            GUI::Animation animation{this->texture_mgr.get(GUI::GameTextures::BackFlipping)};
            animation.setAnimateOnce();
            return animation;
        }
    }
    return GUI::Animation{this->texture_mgr.get(GUI::GameTextures::WormIdle), true};
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

Worm::StateID &Worm::Worm::getState() const {
    return this->state->getState();
}

void Worm::Worm::setWeapon(const WeaponID &id) {
    this->weapon.setWeapon(id);
}

const Worm::WeaponID &Worm::Worm::getWeaponID() const {
    return this->weapon.getWeaponID();
}

void Worm::Worm::setWeaponAngle(float angle) {
    this->weapon.setAngle(angle);
}
