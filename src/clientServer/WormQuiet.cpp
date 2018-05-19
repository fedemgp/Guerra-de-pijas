/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "WormQuiet.h"
#include "Texture.h"

Worm::Quiet::Quiet(GUI::Animation &&animation) : animation(std::move(animation)) {}

Worm::Quiet::~Quiet() {}

void Worm::Quiet::render(int x, int y, SDL_Renderer &renderer) {
    this->animation.render(renderer, x, y);
}

void Worm::Quiet::update(double dt) {
    this->animation.update(dt);
}

IO::PlayerInput Worm::Quiet::moveRight(Worm &w) {
    w.setState(::Worm::StateID::walk);
    w.direction = ::Worm::Direction::right;
    return IO::PlayerInput::moveRight;
}

IO::PlayerInput Worm::Quiet::moveLeft(Worm &w) {
    w.setState(::Worm::StateID::walk);
    w.direction = ::Worm::Direction::left;
    return IO::PlayerInput::moveLeft;
}

IO::PlayerInput Worm::Quiet::stopMove(Worm &w) {
    return IO::PlayerInput::moveNone;
}
