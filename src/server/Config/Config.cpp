/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 01/06/18
 */

#include <yaml-cpp/include/yaml-cpp/yaml.h>
#include <iostream>
#include "Config.h"
/**
 * Meyer's singleton implementation.
 * @return
 */
Game::Config &Game::Config::getInstance() {
    static Config instance(YAML::LoadFile("config.yaml"));
    return instance;
}

Game::Config::Config(const YAML::Node &node) :
        jumpVelocity(node["jumpVelocity"]["x"].as<float>(),
                     node["jumpVelocity"]["y"].as<float>()),
        backflipVelocity(node["backflipVelocity"]["x"].as<float>(),
                         node["backflipVelocity"]["y"].as<float>()){

    std::cout << node << std::endl;
    std::cout << jumpVelocity.x << " " << jumpVelocity.y << std::endl;
}

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
