//
// Created by Gorco on 19/05/18.
//

#include <iostream>
#include <memory>

#include "Player.h"
#include "Player.h"
#include "PlayerStill.h"
#include "PlayerWalk.h"

Worms::Still::Still() : State(Worm::StateID::Still) {}

void Worms::Still::update(Player &p, float dt, b2Body *body) {
    float32 mass = body->GetMass();
    b2Vec2 vel = body->GetLinearVelocity();

    this->impulses[0] = -vel.x * mass;
    body->ApplyLinearImpulse(b2Vec2(impulses[0], impulses[1]), body->GetWorldCenter(), true);
}

void Worms::Still::moveRight(Worms::Player &p) {
    p.setState(Worm::StateID::Walk);
    p.direction = Direction::right;
}

void Worms::Still::moveLeft(Worms::Player &p) {
    p.setState(Worm::StateID::Walk);
    p.direction = Direction::left;
}

void Worms::Still::stopMove(Worms::Player &p) {}

void Worms::Still::jump(Worms::Player &p) {
    p.setState(Worm::StateID::StartJump);
}

void Worms::Still::backFlip(Worms::Player &p) {
    p.setState(Worm::StateID::StartBackFlip);
}

void Worms::Still::bazooka(Worms::Player &p) {
    p.setWeaponID(Worm::WeaponID::WBazooka);
}

void Worms::Still::pointUp(Worms::Player &p) {
    p.increaseWeaponAngle();
}

void Worms::Still::pointDown(Worms::Player &p) {
    p.decreaseWeaponAngle();
}

void Worms::Still::startShot(Worms::Player &p) {
    p.startShot();
}

void Worms::Still::endShot(Worms::Player &p) {
    p.endShot();
}
