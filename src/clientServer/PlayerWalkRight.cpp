#include "Player.h"
#include <memory>
#include "Player.h"
#include "PlayerStill.h"
#include "PlayerWalkLeft.h"
#include "PlayerWalkRight.h"

float Worms::WalkRight::update() {
    return 3.0f;
}

void Worms::WalkRight::moveRight(Worms::Player &p) {}

void Worms::WalkRight::moveLeft(Worms::Player &p) {
    p.state = std::shared_ptr<State>(new WalkLeft());
}

void Worms::WalkRight::stopMove(Worms::Player &p) {
    p.state = std::shared_ptr<State>(new Still());
}

void Worms::WalkRight::jumpRight(Worms::Player &p) {}

void Worms::WalkRight::jumpLeft(Worms::Player &p) {}
