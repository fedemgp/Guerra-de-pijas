/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 01/06/18
 */

#ifndef __GAMECONFIG_H__
#define __GAMECONFIG_H__

#include <stdint.h>
#include <mutex>

#include "Direction.h"
#include "Point.h"
#include "WeaponConfig.h"
#include "WindConfig.h"

#define NUM_TEAMS 2
#define GAME_HEIGHT 30.0f
#define GAME_WIDTH 30.0f
#define WORM_HEALTH 100

namespace Math {
using Vector = Math::Point<float>;
}

namespace Game {

/**
 *  Singleton class with all the game configuration (Velocity constants,
 *  Weapons attributes, etc)
 */
class Config {
   public:
    static Config &getInstance();
    ~Config() = default;

    const Math::Vector getJumpVelocity() const;
    const Math::Vector getBackflipVelocity() const;
    const float getStartJumpTime() const;
    const float getLandTime() const;

    const float getWalkVelocity() const;
    float getSafeFallDistance() const;
    float getMaxFallDamage() const;
    float getMinWindIntensity() const;
    float getMaxWindIntensity() const;

    const uint8_t getTurnTime() const;
    const float getExtraTurnTime() const;
    const float getWaitForNextTurnTime() const;
    const float getPowerChargeTime() const;
    const float getGameWidth() const;
    const float getGameHeight() const;
    const float getDyingTime() const;
    const float getDrowningTime() const;
    const float getBattingTime() const;
    const float getTeleportTime() const;
    const int getWaterLevel() const;
    const uint16_t getWormHealth() const;

    const ::Config::Weapon &getBazookaConfig() const;
    const ::Config::Weapon &getGreenGrenadeConfig() const;
    const uint8_t getClusterFragmentQuantity() const;
    const ::Config::Weapon &getClusterConfig() const;
    const ::Config::Weapon &getMortarConfig() const;
    const ::Config::Weapon &getBananaConfig() const;
    const ::Config::Weapon &getHolyConfig() const;
    const ::Config::Weapon &getClusterFragmentConfig() const;
    const ::Config::Weapon &getMortarFragmentConfig() const;
    const uint8_t getMortarFragmentQuantity() const;
    const ::Config::Weapon &getAerialAttackConfig() const;
    const ::Config::Weapon &getDynamiteConfig() const;
    const uint8_t getAerialAttackMissileQuantity() const;
    const float getAerialAttackMissileSeparation() const;
    const float getAerialAttackLaunchHeight() const;
    const ::Config::Weapon &getTeleportConfig() const;
    const ::Config::Weapon &getBaseballBatConfig() const;

   private:
    /**
     * Constructor hidden because is a singleton.
     * TODO change constructor so it loads information from yaml file
     */
    //    Config();
    explicit Config(const YAML::Node &node);
    Config(Config &copy) = delete;
    Config(Config &&other) = delete;
    Config &operator=(Config &copy) = delete;
    Config &operator=(Config &&other) = delete;

    // jump
    const Math::Vector jumpVelocity;
    const Math::Vector backflipVelocity;
    const float startJumpTime;
    const float landTime;

    // moving
    const float walkVelocity;
    // game
    const float safeFallDistance;
    const float maxFallDamage;
    const std::uint8_t turnTime;
    const float extraTurnTime;
    const float waitForNextTurnTime;
    const float powerChargeTime;
    uint8_t numTeams{NUM_TEAMS};
    float gameWidth{GAME_WIDTH};
    float gameHeight{GAME_HEIGHT};
    uint16_t wormHealth{WORM_HEALTH};
    const float dyingTime;
    const float drowningTime;
    const float battingTime;
    const float teleportTime;
    const int waterLevel;
    //    ::Config::Wind::IntensityRange windRange;
    const float minWindIntensity;
    const float maxWindIntensity;
    // weapons
    const ::Config::Weapon bazooka;
    const ::Config::Weapon greenGrenade;
    const ::Config::Weapon cluster;
    const ::Config::Weapon clusterFragments;
    const uint8_t clusterFragmentQuantity;
    const ::Config::Weapon mortar;
    const ::Config::Weapon mortarFragments;
    const uint8_t mortarFragmentQuantity;
    const ::Config::Weapon banana;
    const ::Config::Weapon holy;
    const uint8_t aerialAttackMissileQuantity;
    const float aerialAttackMissileSeparation;
    const ::Config::Weapon aerialAttack;
    const float aerialAttackLaunchHeight;
    const ::Config::Weapon dynamite;
    const ::Config::Weapon teleport;
    const ::Config::Weapon baseballBat;
};

void endTurn();
}  // namespace Game

#endif  //__GAMECONFIG_H__
