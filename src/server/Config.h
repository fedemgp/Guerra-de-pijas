/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 01/06/18
 */

#ifndef __GAMECONFIG_H__
#define __GAMECONFIG_H__

#include <stdint.h>

#include "Direction.h"
#include "GameConstants.h"
#include "Point.h"

namespace Math {
using Vector = Math::Point<float>;
}

namespace Config {
struct Wind {
    float minIntensity;
    float maxIntensity;
    int xDirection;
    float instensity;
};
    namespace Bullet{
        struct DamageInfo {
            uint16_t damage;
            float radius;
            float impulseDampingRatio;
        };
    } // namespace Bullet

    struct Weapon{
        Bullet::DamageInfo dmgInfo;
        float minAngle;
        float maxAngle;
        float angleStep;
        uint16_t maxShotPower;
        float restitution;
        float friction;
        uint8_t explotionInitialTimeout;
        bool hasAfterExplode;
        float bulletRadius;
        float bulletDampingRatio;
        bool windAffected;
    };

    struct P2PWeapon {
        Bullet::DamageInfo dmgInfo;
        Worm::Direction direction;
        Math::Point<float> position;
        float angle;
    };
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
    float waitForNextTurnTime{WAIT_FOR_NEXT_TURN_TIME};
    float powerChargeTime{POWER_CHARGE_MAX_TIME};
    uint8_t numTeams{NUM_TEAMS};
    float gameWidth{GAME_WIDTH};
    float gameHeight{GAME_HEIGHT};
    float dyingTime{DYING_TIME};
    float drowningTime{DROWNING_TIME};
    float teleportTime{TELEPORT_TIME};
    int waterLevel{WATER_LEVEL};
    float minWindIntensity{MIN_WIND_INTENSITY};
    float maxWindIntensity{MAX_WIND_INTENSITY};
    uint16_t wormHealth{WORM_HEALTH};
    // weapons
    ::Config::Weapon bazooka{
        ::Config::Bullet::DamageInfo{BAZOOKA_DAMAGE, BAZOOKA_DAMAGE_RADIUS, IMPULSE_DAMPING_RATIO},
        BAZOOKA_MIN_ANGLE,
        BAZOOKA_MAX_ANGLE,
        ANGLE_STEP,
        MAX_SHOT_POWER,
        BAZOOKA_RESTITUTION,
        BAZOOKA_FRICTION,
        BAZOOKA_INITIAL_TIMEOUT,
        false,
        BAZOOKA_BULLET_RADIUS,
        BAZOOKA_DAMPING_RATIO,
        true};
    ::Config::Weapon greenGrenade{
            ::Config::Bullet::DamageInfo{GRENADE_DAMAGE, GRENADE_RADIUS, IMPULSE_DAMPING_RATIO},
        GRENADE_MIN_ANGLE,
        GRENADE_MAX_ANGLE,
        ANGLE_STEP,
        MAX_SHOT_POWER,
        GRENADE_RESTITUTION,
        GRENADE_FRICTION,
        GRENADE_INITIAL_TIMEOUT,
        false,
        GRENADE_BULLET_RADIUS,
        GRENADE_DAMPING_RATIO,
        false};
    uint8_t clusterFragmentQuantity{CLUSTER_FRAGMENT_QUANTITY};
    ::Config::Weapon clusterFragments{
            ::Config::Bullet::DamageInfo{CLUSTER_FRAGMENT_DAMAGE, CLUSTER_FRAGMENT_RADIUS, IMPULSE_DAMPING_RATIO},
        CLUSTER_FRAGMENT_MIN_ANGLE,
        CLUSTER_FRAGMENT_MAX_ANGLE,
        CLUSTER_FRAGMENT_ANGLE_STEP,
        CLUSTER_FRAGMENT_SHOT_POWER,
        CLUSTER_FRAGMENT_RESTITUTION,
        CLUSTER_FRAGMENT_FRICTION,
        CLUSTER_FRAGMENT_TIMEOUT,
        false,
        CLUSTER_FRAGMENT_BULLET_RADIUS,
        CLUSTER_FRAGMENT_DAMPING_RATIO,
        false};
    ::Config::Weapon cluster{
            ::Config::Bullet::DamageInfo{CLUSTER_DAMAGE, CLUSTER_RADIUS, IMPULSE_DAMPING_RATIO},
        CLUSTER_MIN_ANGLE,
        CLUSTER_MAX_ANGLE,
        ANGLE_STEP,
        MAX_SHOT_POWER,
        CLUSTER_RESTITUTION,
        CLUSTER_FRICTION,
        CLUSTER_INITIAL_TIMEOUT,
        true,
        CLUSTER_BULLET_RADIUS,
        CLUSTER_DAMPING_RATIO,
        false};
    ::Config::Weapon mortarFragments{
            ::Config::Bullet::DamageInfo{MORTAR_FRAGMENT_DAMAGE, MORTAR_FRAGMENT_RADIUS, IMPULSE_DAMPING_RATIO},
        MORTAR_FRAGMENT_MIN_ANGLE,
        MORTAR_FRAGMENT_MAX_ANGLE,
        MORTAR_FRAGMENT_ANGLE_STEP,
        MORTAR_FRAGMENT_SHOT_POWER,
        MORTAR_FRAGMENT_RESTITUTION,
        MORTAR_FRAGMENT_FRICTION,
        MORTAR_FRAGMENT_TIMEOUT,
        false,
        MORTAR_FRAGMENT_BULLET_RADIUS,
        MORTAR_FRAGMENT_DAMPING_RATIO,
        true};
    uint8_t mortarFragmentQuantity{MORTAR_FRAGMENT_QUANTITY};
    ::Config::Weapon mortar{
            ::Config::Bullet::DamageInfo{MORTAR_DAMAGE, MORTAR_RADIUS, IMPULSE_DAMPING_RATIO},
                          MORTAR_MIN_ANGLE,
                          MORTAR_MAX_ANGLE,
                          ANGLE_STEP,
                          MAX_SHOT_POWER,
                          MORTAR_RESTITUTION,
                          MORTAR_FRICTION,
                          MORTAR_INITIAL_TIMEOUT,
                          true,
                          MORTAR_BULLET_RADIUS,
                          MORTAR_DAMPING_RATIO,
                          true};
    ::Config::Weapon banana{
            ::Config::Bullet::DamageInfo{BANANA_DAMAGE, BANANA_RADIUS, IMPULSE_DAMPING_RATIO},
                          BANANA_MIN_ANGLE,
                          BANANA_MAX_ANGLE,
                          ANGLE_STEP,
                          MAX_SHOT_POWER,
                          BANANA_RESTITUTION,
                          BANANA_FRICTION,
                          BANANA_INITIAL_TIMEOUT,
                          false,
                          BANANA_BULLET_RADIUS,
                          BANANA_DAMPING_RATIO,
                          false};
    ::Config::Weapon holy{
            ::Config::Bullet::DamageInfo{HOLY_DAMAGE, HOLY_RADIUS, IMPULSE_DAMPING_RATIO},
                        HOLY_MIN_ANGLE,
                        HOLY_MAX_ANGLE,
                        ANGLE_STEP,
                        MAX_SHOT_POWER,
                        HOLY_RESTITUTION,
                        HOLY_FRICTION,
                        HOLY_INITIAL_TIMEOUT,
                        false,
                        HOLY_BULLET_RADIUS,
                        HOLY_DAMPING_RATIO,
                        false};
    uint8_t aerialAttackMissileQuantity{AERIAL_ATTACK_MISSILE_QUANTITY};
    float aerialAttackMissileSeparation{AERIAL_ATTACK_MISSILE_SEPARATION};
    ::Config::Weapon aerialAttack{
            ::Config::Bullet::DamageInfo{AERIAL_ATTACK_DAMAGE, AERIAL_ATTACK_RADIUS, IMPULSE_DAMPING_RATIO},
        AERIAL_ATTACK_MIN_ANGLE,
        AERIAL_ATTACK_MAX_ANGLE,
        AERIAL_ATTACK_ANGLE_STEP,
        AERIAL_ATTACK_SHOT_POWER,
        AERIAL_ATTACK_RESTITUTION,
        AERIAL_ATTACK_FRICTION,
        AERIAL_ATTACK_TIMEOUT,
        false,
        AERIAL_ATTACK_BULLET_RADIUS,
        AERIAL_ATTACK_DAMPING_RATIO,
        true};
    const float aerialAttackLaunchHeight{AERIAL_ATTACK_LAUNCH_HEIGHT};
    ::Config::Weapon dynamite{
            ::Config::Bullet::DamageInfo{DYNAMITE_DAMAGE, DYNAMITE_RADIUS, IMPULSE_DAMPING_RATIO},
        DYNAMITE_MIN_ANGLE,
        DYNAMITE_MAX_ANGLE,
        ANGLE_STEP,
        DYNAMITE_MAX_SHOT_POWER,
        DYNAMITE_RESTITUTION,
        DYNAMITE_FRICTION,
        DYNAMITE_INITIAL_TIMEOUT,
        false,
        DYNAMITE_BULLET_RADIUS,
        DYNAMITE_DAMPING_RATIO,
        false};
    ::Config::Weapon teleport{
            ::Config::Bullet::DamageInfo{AERIAL_ATTACK_DAMAGE, AERIAL_ATTACK_RADIUS, IMPULSE_DAMPING_RATIO},
        AERIAL_ATTACK_MIN_ANGLE,
        AERIAL_ATTACK_MAX_ANGLE,
        AERIAL_ATTACK_ANGLE_STEP,
        AERIAL_ATTACK_SHOT_POWER,
        AERIAL_ATTACK_RESTITUTION,
        AERIAL_ATTACK_FRICTION,
        AERIAL_ATTACK_TIMEOUT,
        false,
        AERIAL_ATTACK_BULLET_RADIUS,
        AERIAL_ATTACK_DAMPING_RATIO,
        false};
    ::Config::Weapon baseballBat{
            ::Config::Bullet::DamageInfo{BASEBALL_BAT_DAMAGE, BASEBALL_BAT_DAMAGE_RADIUS,
                                                  BASEBALL_IMPULSE_DAMPING_RATIO},
                               BASEBALL_BAT_MIN_ANGLE, BASEBALL_BAT_MAX_ANGLE, ANGLE_STEP,
                               MAX_SHOT_POWER, BASEBALL_BAT_RESTITUTION, BASEBALL_BAT_FRICTION,
                               BASEBALL_BAT_INITIAL_TIMEOUT, false, BASEBALL_BAT_BULLET_RADIUS,
                               BASEBALL_BAT_DAMPING_RATIO, false};
};

void endTurn();
}  // namespace Game

#endif  //__GAMECONFIG_H__
