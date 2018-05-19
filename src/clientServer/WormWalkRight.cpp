/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <SDL2/SDL_system.h>

#include "Color.h"
#include "GameStateMsg.h"
#include "Worm.h"
#include "WormQuiet.h"
#include "WormWalkLeft.h"
#include "WormWalkRight.h"

Worm::WalkRight::WalkRight(SDL_Renderer &r)
    : animation("src/clientServer/assets/img/Worms/wwalk2.png", r, GUI::Color{0x7f, 0x7f, 0xbb}),
      renderer(r) {
    this->animation.setFlip(SDL_FLIP_HORIZONTAL);
}

Worm::WalkRight::~WalkRight() {}

void Worm::WalkRight::render(int x, int y) {
    this->animation.render(this->renderer, x, y);
}

void Worm::WalkRight::update(double dt) {
    this->animation.update(dt);
}

IO::PlayerInput Worm::WalkRight::moveRight(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::WalkRight::moveLeft(Worm &w) {
    w.state = std::shared_ptr<State>(new WalkLeft(this->renderer));
    return IO::PlayerInput::moveLeft;
}

IO::PlayerInput Worm::WalkRight::stopMove(Worm &w) {
    SDL_RendererFlip flipType = this->animation.getFlip();
    w.state = std::shared_ptr<State>(new Quiet(this->renderer, flipType));
    return IO::PlayerInput::stopMove;
}