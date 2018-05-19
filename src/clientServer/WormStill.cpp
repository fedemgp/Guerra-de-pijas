/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "WormStill.h"
#include "WormWalkLeft.h"
#include "WormWalkRight.h"

Worm::Still::Still(SDL_Renderer &r, SDL_RendererFlip flipType)
    : animation("src/clientServer/assets/img/Worms/wbrth1.png", r, GUI::Color{0x7f, 0x7f, 0xbb}),
      renderer(r) {
    this->animation.setFlip(flipType);
}

Worm::Still::~Still() {}

void Worm::Still::render(int x, int y) {
    this->animation.render(this->renderer, x, y);
}

void Worm::Still::update(float dt) {
    this->animation.update(dt);
}

IO::PlayerInput Worm::Still::moveRight(Worm &w) {
    w.state = std::shared_ptr<State>(new WalkRight(this->renderer));
    return IO::PlayerInput::moveRight;
}

IO::PlayerInput Worm::Still::moveLeft(Worm &w) {
    w.state = std::shared_ptr<State>(new WalkLeft(this->renderer));
    return IO::PlayerInput::moveLeft;
}

IO::PlayerInput Worm::Still::stopMove(Worm &w) {
    return IO::PlayerInput::moveNone;
}
