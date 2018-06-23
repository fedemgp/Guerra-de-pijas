/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 01/06/18
 */

#include <iostream>

#include "Config.h"
#include "ConfigDefines.h"
#include "yaml-cpp/include/yaml-cpp/yaml.h"
/**
 * Meyer's singleton implementation.
 * @return
 */
Game::Config &Game::Config::getInstance() {
    static Config instance(YAML::LoadFile(CONFIG_PATH));
    return instance;
}

Game::Config::Config(const YAML::Node &node)
    : jumpVelocity(node[JUMP][VELOCITY][X].as<float>(), node[JUMP][VELOCITY][Y].as<float>()),
      backflipVelocity(node[BACKFLIP][VELOCITY][X].as<float>(),
                       node[BACKFLIP][VELOCITY][Y].as<float>()),
      startJumpTime(node[JUMP][START_TIME].as<float>()),
      landTime(node[JUMP][LAND_TIME].as<float>()),
      walkVelocity(node[WALK][VELOCITY].as<float>()),
      safeFallDistance(node[GAME][SAFE_FALL_DISTANCE].as<float>()),
      maxFallDamage(node[GAME][MAX_FALL_DAMAGE].as<float>()),
      turnTime((std::uint8_t)node[GAME][TURN_TIME].as<unsigned int>()),
      extraTurnTime(node[GAME][EXTRA_TURN_TIME].as<float>()),
      waitForNextTurnTime(node[GAME][WAIT_FOR_NEXT_TURN_TIME].as<float>()),
      powerChargeTime(node[GAME][POWER_CHARGE_MAX_TIME].as<float>()),
      dyingTime(node[GAME][DYING_TIME].as<float>()),
      drowningTime(node[GAME][DROWNING_TIME].as<float>()),
      teleportTime(node[GAME][TELEPORT_TIME].as<float>()),
      waterLevel(node[GAME][WATER_LEVEL].as<int>()),
      minWindIntensity(node[WIND_INTENSITY][MIN].as<float>()),
      maxWindIntensity(node[WIND_INTENSITY][MAX].as<float>()),
      bazooka(node[BAZOOKA]),
      greenGrenade(node[GRENADE]),
      cluster(node[CLUSTER]),
      clusterFragments(node[CLUSTER][FRAGMENT]),
      clusterFragmentQuantity((std::uint8_t)node[CLUSTER][FRAGMENT][QUANTITY].as<unsigned int>()),
      mortar(node[MORTAR]),
      mortarFragments(node[MORTAR][FRAGMENT]),
      mortarFragmentQuantity((std::uint8_t)node[MORTAR][FRAGMENT][QUANTITY].as<unsigned int>()),
      banana(node[BANANA]),
      holy(node[HOLY]),
      aerialAttackMissileQuantity(
          (std::uint8_t)node[AERIAL_ATTACK][BULLET][QUANTITY].as<unsigned int>()),
      aerialAttackMissileSeparation(node[AERIAL_ATTACK][BULLET][SEPARATION].as<float>()),
      aerialAttack(node[AERIAL_ATTACK]),
      aerialAttackLaunchHeight(node[AERIAL_ATTACK][LAUNCH_HEIGHT].as<float>()),
      dynamite(node[DYNAMITE]),
      teleport(node[TELEPORT]),
      baseballBat(node[BASEBALL_BAT]) {}

float Game::Config::getSafeFallDistance() const {
    return this->safeFallDistance;
}

float Game::Config::getMaxFallDamage() const {
    return this->maxFallDamage;
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

const Config::Weapon &Game::Config::getBazookaConfig() const {
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

const Config::Weapon &Game::Config::getGreenGrenadeConfig() const {
    return this->greenGrenade;
}

const Config::Weapon &Game::Config::getClusterConfig() const {
    return this->cluster;
}

const Config::Weapon &Game::Config::getMortarConfig() const {
    return this->mortar;
}

const Config::Weapon &Game::Config::getBananaConfig() const {
    return this->banana;
}

const Config::Weapon &Game::Config::getHolyConfig() const {
    return this->holy;
}

const float Game::Config::getPowerChargeTime() const {
    return this->powerChargeTime;
}

const Config::Weapon &Game::Config::getClusterFragmentConfig() const {
    return this->clusterFragments;
}

const uint8_t Game::Config::getClusterFragmentQuantity() const {
    return this->clusterFragmentQuantity;
}

const Config::Weapon &Game::Config::getMortarFragmentConfig() const {
    return this->mortarFragments;
}

const uint8_t Game::Config::getMortarFragmentQuantity() const {
    return this->mortarFragmentQuantity;
}

const float Game::Config::getWaitForNextTurnTime() const {
    return this->waitForNextTurnTime;
}

const Config::Weapon &Game::Config::getAerialAttackConfig() const {
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

const Config::Weapon &Game::Config::getTeleportConfig() const {
    return this->teleport;
}

const float Game::Config::getTeleportTime() const {
    return this->teleportTime;
}

const Config::Weapon &Game::Config::getDynamiteConfig() const {
    return this->dynamite;
}

const Config::Weapon &Game::Config::getBaseballBatConfig() const {
    return this->baseballBat;
}

float Game::Config::getMinWindIntensity() const {
    return this->minWindIntensity;
}

float Game::Config::getMaxWindIntensity() const {
    return this->maxWindIntensity;
}
