/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 01/06/18
 */

#ifndef __GAMECONFIG_H__
#define __GAMECONFIG_H__

#include <stdint-gcc.h>

#include "GameConstants.h"
#include "Point.h"

namespace Math {
using Vector = Math::Point<float>;
}

namespace Game {
namespace Weapon {
struct Config {
   public:
    uint16_t damage;
    float damageRadius;
    float minAngle;
    float maxAngle;
    float angleStep;
    uint16_t maxShotPower;
    float restitution;
    float friction;
};
}  // namespace Weapon
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

    const uint8_t getTurnTime() const;
    const float getExtraTurnTime() const;
    const float getPowerChargeTime() const;
    const uint8_t getNumTeams() const;
    const float getGameWidth() const;
    const float getGameHeight() const;
    const float getDyingTime() const;
    const float getDrowningTime() const;
    const int getWaterLevel() const;
    const uint16_t getWormHealth() const;

    const Weapon::Config &getBazookaConfig() const;
    const Weapon::Config &getGreenGrenadeConfig() const;
    const Weapon::Config &getClusterConfig() const;
    const Weapon::Config &getMortarConfig() const;
    const Weapon::Config &getBananaConfig() const;
    const Weapon::Config &getHolyConfig() const;

   private:
    /**
     * Constructor hidden because is a singleton.
     * TODO change constructor so it loads information from yaml file
     */
    Config();
    Config(Config &copy) = delete;
    Config(Config &&other) = delete;
    Config &operator=(Config &copy) = delete;
    Config &operator=(Config &&other) = delete;
    // jump
    Math::Vector jumpVelocity;
    Math::Vector backflipVelocity;
    float startJumpTime{START_JUMP_TIME};
    float landTime{JUMP_LAND_TIME};
    // moving
    float walkVelocity{WALK_VELOCITY};
    // game
    uint8_t turnTime{TURN_TIME};
    float extraTurnTime{EXTRA_TURN_TIME};
    float powerChargeTime{POWER_CHARGE_MAX_TIME};
    uint8_t numTeams{NUM_TEAMS};
    float gameWidth{GAME_WIDTH};
    float gameHeight{GAME_HEIGHT};
    float dyingTime{DYING_TIME};
    float drowningTime{DROWNING_TIME};
    int waterLevel{WATER_LEVEL};
    uint16_t wormHealth{WORM_HEALTH};
    // weapons
    Weapon::Config bazooka{
        BAZOOKA_DAMAGE, BAZOOKA_DAMAGE_RADIUS, BAZOOKA_MIN_ANGLE,   BAZOOKA_MAX_ANGLE,
        ANGLE_STEP,     MAX_SHOT_POWER,        BAZOOKA_RESTITUTION, BAZOOKA_FRCTION};
    Weapon::Config greenGrenade{GRENADE_DAMAGE,      GRENADE_RADIUS, GRENADE_MIN_ANGLE,
                                GRENADE_MAX_ANGLE,   ANGLE_STEP,     MAX_SHOT_POWER,
                                GRENADE_RESTITUTION, GRENADE_FRCTION};
    Weapon::Config cluster{CLUSTER_DAMAGE, CLUSTER_RADIUS, CLUSTER_MIN_ANGLE,   CLUSTER_MAX_ANGLE,
                           ANGLE_STEP,     MAX_SHOT_POWER, CLUSTER_RESTITUTION, CLUSTER_FRCTION};
    Weapon::Config mortar{MORTAR_DAMAGE, MORTAR_RADIUS,  MORTAR_MIN_ANGLE,   MORTAR_MAX_ANGLE,
                          ANGLE_STEP,    MAX_SHOT_POWER, MORTAR_RESTITUTION, MORTAR_FRCTION};
    Weapon::Config banana{BANANA_DAMAGE, BANANA_RADIUS,  BANANA_MIN_ANGLE,   BANANA_MAX_ANGLE,
                          ANGLE_STEP,    MAX_SHOT_POWER, BANANA_RESTITUTION, BANANA_FRCTION};
    Weapon::Config holy{HOLY_DAMAGE, HOLY_RADIUS,    HOLY_MIN_ANGLE,   HOLY_MAX_ANGLE,
                        ANGLE_STEP,  MAX_SHOT_POWER, HOLY_RESTITUTION, HOLY_FRCTION};
};
}  // namespace Game

#endif  //__GAMECONFIG_H__
