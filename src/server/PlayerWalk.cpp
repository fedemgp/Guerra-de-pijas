
#include <iostream>
#include <memory>

#include "Player.h"
#include "PlayerStill.h"
#include "PlayerWalk.h"

void Worms::Walk::update(Player &p, float dt, b2Body *body) {
    float32 mass = body->GetMass();
    b2Vec2 vel = body->GetLinearVelocity();

    float final_vel{0.0f};

    if (!p.isOnGround()) {
        this->impulses[0] = -vel.x * mass;
        body->ApplyLinearImpulse(b2Vec2(impulses[0], impulses[1]), body->GetWorldCenter(), true);
        p.notify(p, Event::WormFalling);
        p.setState(Worm::StateID::Falling);
        return;
    }

    if (p.direction == Direction::left) {
        final_vel = -this->walkVelocity;
    } else {
        final_vel = this->walkVelocity;
    }

    this->impulses[0] = mass * (final_vel - vel.x);
    body->ApplyLinearImpulse(b2Vec2(this->impulses[0], this->impulses[1]), body->GetWorldCenter(),
                             true);

    p.lastWalkDirection = p.direction;

    this->timeElapsed += dt;
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

Worms::Walk::Walk()
    : State(Worm::StateID::Walk), walkVelocity(Game::Config::getInstance().getWalkVelocity()) {}

void Worms::Walk::backFlip(Worms::Player &p) {}

void Worms::Walk::bazooka(Worms::Player &p) {}

void Worms::Walk::pointUp(Worms::Player &p) {}

void Worms::Walk::pointDown(Worms::Player &p) {}

void Worms::Walk::startShot(Worms::Player &p) {}

void Worms::Walk::endShot(Worms::Player &p) {}

void Worms::Walk::grenade(Worms::Player &p) {}

void Worms::Walk::cluster(Worms::Player &p) {}

void Worms::Walk::mortar(Worms::Player &p) {}

void Worms::Walk::banana(Worms::Player &p) {}

void Worms::Walk::holy(Worms::Player &p) {}

void Worms::Walk::setTimeout(Worms::Player &p, uint8_t time) {}
