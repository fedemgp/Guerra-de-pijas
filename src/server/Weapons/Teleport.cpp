//
// Created by rodrigo on 16/06/18.
//

#include "Teleport.h"

#define CONFIG Game::Config::getInstance()

Weapon::Teleport::Teleport()
    : Weapon::Weapon(CONFIG.getTeleportConfig(), Worm::WeaponID::WTeleport, 0.0) {}

void Weapon::Teleport::update(float dt) {}

void Weapon::Teleport::startShot(Worms::Player *player) {}

void Weapon::Teleport::endShot() {}

void Weapon::Teleport::setTimeout(uint8_t time) {}

std::list<Worms::Bullet> Weapon::Teleport::onExplode(const Worms::Bullet &mainBullet,
                                                     Worms::Physics &physics) {
    return std::move(std::list<Worms::Bullet>());
}

void Weapon::Teleport::positionSelected(Worms::Player &p, Math::Point<float> point) {
    p.teleportPosition = point;
    p.setState(Worm::StateID::Teleporting);
}

void Weapon::Teleport::increaseAngle() {}

void Weapon::Teleport::decreaseAngle() {}
