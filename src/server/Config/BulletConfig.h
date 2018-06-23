/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 22/06/18
 */

#ifndef __BULLET_CONFIG_H__
#define __BULLET_CONFIG_H__

#include "yaml-cpp/yaml.h"
#include <cstdint>

namespace Config {
namespace Bullet {
struct DamageInfo {
    std::uint16_t damage;
    float radius;
    float impulseDampingRatio;

    explicit DamageInfo(const YAML::Node &config);
};
}  // namespace Bullet
}  // namespace Bullet

#endif  //__BULLET_CONFIG_H__
