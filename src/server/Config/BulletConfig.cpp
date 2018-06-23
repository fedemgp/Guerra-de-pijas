/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 22/06/18
 */

#include "BulletConfig.h"
#include "ConfigDefines.h"

Config::Bullet::DamageInfo::DamageInfo(const YAML::Node &config)
    : damage((std::uint16_t)config[DAMAGE].as<unsigned int>()),
      radius(config[RADIUS].as<float>()),
      impulseDampingRatio(config[IMPULSE_DAMPING_RATIO].as<float>()) {}
