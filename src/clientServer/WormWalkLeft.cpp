/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include "WormWalkLeft.h"
#include "WormStill.h"
#include "WormWalkRight.h"

Worm::WalkLeft::WalkLeft(SDL_Renderer &r)
    : animation("src/clientServer/assets/img/Worms/wwalk2.png", r, GUI::Color{0x7f, 0x7f, 0xbb}),
      renderer(r) {
    this->animation.setFlip(SDL_FLIP_NONE);
}

Worm::WalkLeft::~WalkLeft() {}

void Worm::WalkLeft::render(int x, int y) {
    this->animation.render(this->renderer, x, y);
}

void Worm::WalkLeft::update(float dt) {
    this->animation.update(dt);
}

IO::PlayerInput Worm::WalkLeft::moveLeft(Worm &w) {
    return IO::PlayerInput::moveNone;
}

IO::PlayerInput Worm::WalkLeft::moveRight(Worm &w) {
    w.state = std::shared_ptr<State>(new WalkRight(this->renderer));
    return IO::PlayerInput::moveRight;
}
/**
 * get his flip configuration and pass it to the Worm::Still constructor.
 * This is needed to keep orientation of the worm
 * @param worm
 * @return stopMove
 */
IO::PlayerInput Worm::WalkLeft::stopMove(Worm &w) {
    SDL_RendererFlip flipType = this->animation.getFlip();
    w.state = std::shared_ptr<State>(new Still(this->renderer, flipType));
    return IO::PlayerInput::stopMove;
}