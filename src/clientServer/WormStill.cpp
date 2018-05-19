/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "WormStill.h"
#include "Texture.h"

Worm::Still::Still(GUI::Animation &&animation) : animation(std::move(animation)) {}

Worm::Still::~Still() {}

void Worm::Still::render(int x, int y, SDL_Renderer &renderer) {
    this->animation.render(renderer, x, y);
}

void Worm::Still::update(float dt) {
    this->animation.update(dt);
}

IO::PlayerInput Worm::Still::moveRight(Worm &w) {
    w.setState(::Worm::StateID::walk);
    w.direction = ::Worm::Direction::right;
    this->animation.setFlip(SDL_FLIP_HORIZONTAL);
    return IO::PlayerInput::moveRight;
}

IO::PlayerInput Worm::Still::moveLeft(Worm &w) {
    w.setState(::Worm::StateID::walk);
    this->animation.setFlip(SDL_FLIP_NONE);
    w.direction = ::Worm::Direction::left;
    return IO::PlayerInput::moveLeft;
}

IO::PlayerInput Worm::Still::stopMove(Worm &w) {
    return IO::PlayerInput::moveNone;
}
