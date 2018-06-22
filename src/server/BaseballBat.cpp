//
// Created by rodrigo on 16/06/18.
//

#include "BaseballBat.h"
#include "Direction.h"
#include "Player.h"

Weapon::BaseballBat::BaseballBat(float angle)
    : Worms::Weapon(Game::Config::getInstance().getBaseballBatConfig(),
                    Worm::WeaponID::WBaseballBat, angle),
      weaponInfo{this->config.dmgInfo, Worm::Direction::left, {0, 0}} {}

void Weapon::BaseballBat::update(float dt) {}

void Weapon::BaseballBat::startShot(Worms::Player *player) {
    this->weaponInfo.position = player->getPosition();
    this->weaponInfo.direction = player->direction;
    this->weaponInfo.angle = this->angle;
}

void Weapon::BaseballBat::endShot() {}

void Weapon::BaseballBat::setTimeout(uint8_t time) {}

std::list<Worms::Bullet> Weapon::BaseballBat::onExplode(const Worms::Bullet &mainBullet,
                                                        Worms::Physics &physics) {
    return std::move(std::list<Worms::Bullet>());
}

void Weapon::BaseballBat::positionSelected(Worms::Player &p, Math::Point<float> point) {}

Config::P2PWeapon &Weapon::BaseballBat::getWeaponInfo() {
    return this->weaponInfo;
}
