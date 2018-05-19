//
// Created by Gorco on 19/05/18.
//

#include <memory>

#include "Player.h"
#include "Player.h"
#include "PlayerStill.h"
#include "PlayerWalkRight.h"
#include "PlayerWalkLeft.h"

float Worms::Still::update() {
    return 0.0f;
}

void Worms::Still::moveRight(Worms::Player &p) {
    p.state = std::shared_ptr<State>(new WalkRight());
}

void Worms::Still::moveLeft(Worms::Player &p) {
    p.state = std::shared_ptr<State>(new WalkLeft());
}

void Worms::Still::stopMove(Worms::Player &p) {

}

void Worms::Still::jumpRight(Worms::Player &p) {

}

void Worms::Still::jumpLeft(Worms::Player &p) {

}
