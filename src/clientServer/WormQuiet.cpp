/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "WormQuiet.h"
#include "WormWalkLeft.h"
#include "WormWalkRight.h"

Worm::Quiet::Quiet(SDL_Renderer &r, SDL_RendererFlip flipType)
    : animation("src/clientServer/assets/img/Worms/wwalk2.png", r, GUI::Color{0x7f, 0x7f, 0xbb}),
      renderer(r) {
    this->animation.setFlip(flipType);
}

Worm::Quiet::~Quiet() {}

void Worm::Quiet::render(int x, int y) {
    this->animation.render(this->renderer, x, y);
}

void Worm::Quiet::update(double dt) {
    this->animation.update(dt);
}

IO::PlayerInput Worm::Quiet::moveRight(Worm &w) {
    w.state = std::shared_ptr<State>(new WalkRight(this->renderer));
    return IO::PlayerInput::moveRight;
}

IO::PlayerInput Worm::Quiet::moveLeft(Worm &w) {
    w.state = std::shared_ptr<State>(new WalkLeft(this->renderer));
    return IO::PlayerInput::moveLeft;
}

IO::PlayerInput Worm::Quiet::stopMove(Worm &w) {
    return IO::PlayerInput::moveNone;
}
