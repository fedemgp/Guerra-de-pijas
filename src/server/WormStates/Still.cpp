//
// Created by Gorco on 19/05/18.
//

#include <cstdint>
#include <iostream>
#include <memory>

#include "../Player.h"
#include "Still.h"
#include "Walk.h"

Worms::Still::Still() : State(Worm::StateID::Still) {}

void Worms::Still::update(Player &p, float dt, b2Body *body) {
    float32 mass = body->GetMass();
    b2Vec2 vel = body->GetLinearVelocity();

    this->impulses[0] = -vel.x * mass;
    body->ApplyLinearImpulse(b2Vec2(impulses[0], impulses[1]), body->GetWorldCenter(), true);
}

void Worms::Still::moveRight(Worms::Player &p) {
    p.direction = Worm::Direction::right;
    p.setState(Worm::StateID::Walk);
}

void Worms::Still::moveLeft(Worms::Player &p) {
    p.direction = Worm::Direction::left;
    p.setState(Worm::StateID::Walk);
}

void Worms::Still::stopMove(Worms::Player &p) {}

void Worms::Still::jump(Worms::Player &p) {
    p.notify(p, Event::WormFalling);
    p.setState(Worm::StateID::StartJump);
}

void Worms::Still::backFlip(Worms::Player &p) {
    p.notify(p, Event::WormFalling);
    p.setState(Worm::StateID::StartBackFlip);
}

void Worms::Still::bazooka(Worms::Player &p) {
    p.setWeapon(Worm::WeaponID::WBazooka);
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

void Worms::Still::grenade(Worms::Player &p) {
    p.setWeapon(Worm::WeaponID::WGrenade);
}

void Worms::Still::cluster(Worms::Player &p) {
    p.setWeapon(Worm::WeaponID::WCluster);
}

void Worms::Still::mortar(Worms::Player &p) {
    p.setWeapon(Worm::WeaponID::WMortar);
}

void Worms::Still::banana(Worms::Player &p) {
    p.setWeapon(Worm::WeaponID::WBanana);
}

void Worms::Still::holy(Worms::Player &p) {
    p.setWeapon(Worm::WeaponID::WHoly);
}

void Worms::Still::setTimeout(Worms::Player &p, uint8_t time) {
    p.setWeaponTimeout(time);
}

void Worms::Still::aerialAttack(Worms::Player &p) {
    p.setWeapon(Worm::WeaponID::WAerial);
}

void Worms::Still::dynamite(Worms::Player &p) {
    p.setWeapon(Worm::WeaponID::WDynamite);
}

void Worms::Still::teleport(Worms::Player &p) {
    p.setWeapon(Worm::WeaponID::WTeleport);
}

void Worms::Still::baseballBat(Worms::Player &p) {
    p.setWeapon(Worm::WeaponID::WBaseballBat);
}
