//
// Created by rodrigo on 28/05/18.
//

#include "NoWeapons.h"
#include "Player.h"

Worms::NoWeapons::NoWeapons() : State(Worm::StateID::NoWeapons) {}

void Worms::NoWeapons::update(Worms::Player &p, float dt, b2Body *body) {
    float32 mass = body->GetMass();
    b2Vec2 vel = body->GetLinearVelocity();

    this->impulses[0] = -vel.x * mass;
    body->ApplyLinearImpulse(b2Vec2(impulses[0], impulses[1]), body->GetWorldCenter(), true);
}

void Worms::NoWeapons::moveRight(Worms::Player &p) {
    p.setState(Worm::StateID::Walk);
    p.direction = Direction::right;
}

void Worms::NoWeapons::moveLeft(Worms::Player &p) {
    p.setState(Worm::StateID::Walk);
    p.direction = Direction::left;
}

void Worms::NoWeapons::jump(Worms::Player &p) {
    p.setState(Worm::StateID::StartJump);
}

void Worms::NoWeapons::stopMove(Worms::Player &p) {}

void Worms::NoWeapons::backFlip(Worms::Player &p) {
    p.setState(Worm::StateID::StartBackFlip);
}

void Worms::NoWeapons::bazooka(Worms::Player &p) {}

void Worms::NoWeapons::pointUp(Worms::Player &p) {}

void Worms::NoWeapons::pointDown(Worms::Player &p) {}

void Worms::NoWeapons::startShot(Worms::Player &p) {}

void Worms::NoWeapons::endShot(Worms::Player &p) {}
