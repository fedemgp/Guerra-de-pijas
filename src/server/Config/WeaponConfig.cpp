/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 22/06/18
 */

#include "ConfigDefines.h"
#include "WeaponConfig.h"

Config::Weapon::Weapon(const YAML::Node &config):
        dmgInfo(config[BULLET][DAMAGE]),
        minAngle(config[ANGLE][MIN].as<float>()),
        maxAngle(config[ANGLE][MAX].as<float>()),
        angleStep(config[ANGLE][STEP].as<float>()),
        maxShotPower((std::uint16_t) config[MAX_SHOT_POWER].as<unsigned int>()),
        restitution(config[BULLET][RESTITUTION].as<float>()),
        friction(config[BULLET][FRICTION].as<float>()),
        explotionInitialTimeout((std::uint8_t) config[BULLET][EXPLOTION_INITIAL_TIMEOUT].as<unsigned int>()),
        hasAfterExplode(config[HAS_AFTER_EXPLODE].as<bool>()),
        bulletRadius(config[BULLET][RADIUS].as<float>()),
        bulletDampingRatio(config[BULLET][DAMAGE][DAMPING_RATIO].as<float>()),
        windAffected(config[BULLET][WIND_AFFECTED].as<bool>()){}
