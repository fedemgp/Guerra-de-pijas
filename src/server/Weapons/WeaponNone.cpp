/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 24/06/18
 */

#include "WeaponNone.h"

#define CONFIG Game::Config::getInstance()

Weapon::WeaponNone::WeaponNone()
    : Weapon::Weapon(CONFIG.getTeleportConfig(), Worm::WeaponID::WNone, 0.0) {}

std::list<Worms::Bullet> Weapon::WeaponNone::onExplode(const Worms::Bullet &mainBullet,
                                                       Worms::Physics &physics) {
    return std::move(std::list<Worms::Bullet>());
}
