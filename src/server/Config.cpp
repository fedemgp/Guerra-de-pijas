/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 01/06/18
 */

#include "Config.h"
/**
 * Meyer's singleton implementation.
 * @return
 */
Game::Config &Game::Config::getInstance() {
    static Config instance;
    return instance;
}

Game::Config::Config()
    : jumpVelocity(JUMP_VEL_X, JUMP_VEL_Y), backflipVelocity(BACKFLIP_VEL_X, BACKFLIP_VEL_Y) {}

float Game::Config::getSafeFallDistance() const {
    return 6.0f;
}

float Game::Config::getMaxFallDamage() const {
    return 25.0f;
}

const Math::Vector Game::Config::getJumpVelocity() const {
    return this->jumpVelocity;
}

const float Game::Config::getStartJumpTime() const {
    return this->startJumpTime;
}

const float Game::Config::getLandTime() const {
    return this->landTime;
}

const Math::Vector Game::Config::getBackflipVelocity() const {
    return this->backflipVelocity;
}

const uint8_t Game::Config::getTurnTime() const {
    return this->turnTime;
}

const float Game::Config::getGameWidth() const {
    return this->gameWidth;
}

const float Game::Config::getGameHeight() const {
    return this->gameHeight;
}

const uint16_t Game::Config::getWormHealth() const {
    return this->wormHealth;
}

const Game::Weapon::Config &Game::Config::getBazookaConfig() const {
    return this->bazooka;
}

const float Game::Config::getDyingTime() const {
    return this->dyingTime;
}

const float Game::Config::getDrowningTime() const {
    return this->drowningTime;
}

const float Game::Config::getExtraTurnTime() const {
    return this->extraTurnTime;
}

const int Game::Config::getWaterLevel() const {
    return this->waterLevel;
}

const float Game::Config::getWalkVelocity() const {
    return this->walkVelocity;
}

const Game::Weapon::Config &Game::Config::getGreenGrenadeConfig() const {
    return this->greenGrenade;
}

const Game::Weapon::Config &Game::Config::getClusterConfig() const {
    return this->cluster;
}

const Game::Weapon::Config &Game::Config::getMortarConfig() const {
    return this->mortar;
}

const Game::Weapon::Config &Game::Config::getBananaConfig() const {
    return this->banana;
}

const Game::Weapon::Config &Game::Config::getHolyConfig() const {
    return this->holy;
}

const float Game::Config::getPowerChargeTime() const {
    return this->powerChargeTime;
}

const Game::Weapon::Config &Game::Config::getClusterFragmentConfig() const {
    return this->clusterFragments;
}

const uint8_t Game::Config::getClusterFragmentQuantity() const {
    return this->clusterFragmentQuantity;
}

const Game::Weapon::Config &Game::Config::getMortarFragmentConfig() const {
    return this->mortarFragments;
}

const uint8_t Game::Config::getMortarFragmentQuantity() const {
    return this->mortarFragmentQuantity;
}

const float Game::Config::getWaitForNextTurnTime() const {
    return this->waitForNextTurnTime;
}

const Game::Weapon::Config &Game::Config::getAerialAttackConfig() const {
    return this->aerialAttack;
}

const uint8_t Game::Config::getAerialAttackMissileQuantity() const {
    return this->aerialAttackMissileQuantity;
}

const float Game::Config::getAerialAttackMissileSeparation() const {
    return this->aerialAttackMissileSeparation;
}

const float Game::Config::getAerialAttackLaunchHeight() const {
    return this->aerialAttackLaunchHeight;
}

const Game::Weapon::Config &Game::Config::getTeleportConfig() const {
    return this->teleport;
}

const float Game::Config::getTeleportTime() const {
    return this->teleportTime;
}

const Game::Weapon::Config &Game::Config::getDynamiteConfig() const {
    return this->dynamite;
}
