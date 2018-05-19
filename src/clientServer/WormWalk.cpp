/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "WormWalk.h"
#include "WormQuiet.h"

Worm::Walk::Walk(GUI::Animation &&animation) : animation(std::move(animation)) {
    this->animation.setFlip(SDL_FLIP_NONE);
}

Worm::Walk::~Walk() {}

void Worm::Walk::render(int x, int y, SDL_Renderer &renderer) {
    this->animation.render(renderer, x, y);
}

void Worm::Walk::update(double dt) {
    this->animation.update(dt);
}

IO::PlayerInput Worm::Walk::moveLeft(Worm &w) {
    this->animation.setFlip(SDL_FLIP_NONE);
    w.direction = Direction::left;
    this->animation.reset();
    return IO::PlayerInput::moveLeft;
}

IO::PlayerInput Worm::Walk::moveRight(Worm &w) {
    this->animation.setFlip(SDL_FLIP_HORIZONTAL);
    w.direction = Direction::right;
    this->animation.reset();
    return IO::PlayerInput::moveRight;
}

IO::PlayerInput Worm::Walk::stopMove(Worm &w) {
    w.setState(StateID::quiet);
    return IO::PlayerInput::stopMove;
}
