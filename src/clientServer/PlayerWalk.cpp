
#include "Player.h"
#include <memory>
#include "Player.h"
#include "PlayerStill.h"
#include "PlayerWalk.h"

const std::vector<float> & Worms::Walk::update(Player &p, float dt, float32 mass,
                                               const b2Vec2 &vel) {
    float final_vel{0.0f};
    if (p.direction == Direction::left) {
        final_vel = -3.0f;
    } else {
        final_vel = 3.0f;
    }
    this->impulses[0] = mass * (final_vel - vel.x);
    return this->impulses;
}

void Worms::Walk::moveRight(Worms::Player &p) {
    p.direction = Direction::right;
}

void Worms::Walk::moveLeft(Worms::Player &p) {
    p.direction = Direction::left;
}

void Worms::Walk::stopMove(Worms::Player &p) {
    p.setState(Worm::StateID::Still);
}

void Worms::Walk::jump(Worms::Player &p) {}

Worms::Walk::Walk() : State(Worm::StateID::Walk) {}
