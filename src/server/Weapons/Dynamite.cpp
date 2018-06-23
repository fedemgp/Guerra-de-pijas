/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 16/06/18
 */

#include "Dynamite.h"
#include "../Player.h"

#define CONFIG Game::Config::getInstance()

Weapon::Dynamite::Dynamite()
    : Worms::Weapon(CONFIG.getDynamiteConfig(), Worm::WeaponID::WDynamite, angle) {}

void Weapon::Dynamite::update(float dt) {}

void Weapon::Dynamite::startShot(Worms::Player *player) {}

void Weapon::Dynamite::endShot() {}

void Weapon::Dynamite::setTimeout(uint8_t time) {
    this->timeLimit = time;
}

std::list<Worms::Bullet> Weapon::Dynamite::onExplode(const Worms::Bullet &mainBullet,
                                                     Worms::Physics &physics) {
    return std::list<Worms::Bullet>();
}

void Weapon::Dynamite::positionSelected(Worms::Player &p, Math::Point<float> point) {}

void Weapon::Dynamite::increaseAngle() {}

void Weapon::Dynamite::decreaseAngle() {}
