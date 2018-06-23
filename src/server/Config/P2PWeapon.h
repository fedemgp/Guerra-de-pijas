/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 22/06/18
 */

#ifndef __P2PWeapon_H__
#define __P2PWeapon_H__


#include <Direction.h>
#include <Point.h>

#include "BulletConfig.h"

namespace Config {
    struct P2PWeapon {
        Bullet::DamageInfo dmgInfo;
        Worm::Direction direction;
        Math::Point<float> position;
        float angle;
    };
} // namespace Config


#endif //__P2PWeapon_H__
