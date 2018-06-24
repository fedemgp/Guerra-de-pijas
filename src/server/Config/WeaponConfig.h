/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 22/06/18
 */

#ifndef __WeaponConfig_H__
#define __WeaponConfig_H__

#include "yaml-cpp/node/node.h"
#include <cstdint>

#include "BulletConfig.h"

namespace Config {
struct Weapon {
    Bullet::DamageInfo dmgInfo;
    float minAngle;
    float maxAngle;
    float angleStep;
    std::uint16_t maxShotPower;
    float restitution;
    float friction;
    std::uint8_t explotionInitialTimeout;
    bool hasAfterExplode;
    float bulletRadius;
    float bulletDampingRatio;
    bool windAffected;

    explicit Weapon(const YAML::Node &config);
};
}  // namespace Config

#endif  //__WeaponConfig_H__
