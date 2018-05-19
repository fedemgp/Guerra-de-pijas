
#include <memory>
#include "Player.h"
#include "PlayerWalkLeft.h"
#include "PlayerWalkRight.h"
#include "PlayerStill.h"

float Worms::WalkLeft::update() {
    return -3.0f;
}

void Worms::WalkLeft::moveRight(Worms::Player &p) {
    p.state = std::shared_ptr<State>(new WalkRight());
}

void Worms::WalkLeft::moveLeft(Worms::Player &p) {

}

void Worms::WalkLeft::stopMove(Worms::Player &p) {
    p.state = std::shared_ptr<State>(new Still());
}
