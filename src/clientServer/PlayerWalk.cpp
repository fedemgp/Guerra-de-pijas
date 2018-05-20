
#include "Player.h"
#include <memory>
#include "Player.h"
#include "PlayerStill.h"
#include "PlayerWalk.h"

float Worms::Walk::update(Player &p) {
    if (p.direction == Direction::left) {
        return -3.0f;
    } else {
        return 3.0f;
    }
}

void Worms::Walk::moveRight(Worms::Player &p) {
    p.direction = Direction::right;
}

void Worms::Walk::moveLeft(Worms::Player &p) {
    p.direction = Direction::left;
}

void Worms::Walk::stopMove(Worms::Player &p) {
    p.state = std::shared_ptr<State>(new Still());
}

void Worms::Walk::jump(Worms::Player &p) {}

