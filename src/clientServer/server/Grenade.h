/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#ifndef __GRENADE_H__
#define __GRENADE_H__

#include "Weapon.h"

namespace Weapon{
    class Grenade: public Worms::Weapon{
    public:
        Grenade(float angle);
        ~Grenade() override = default;
        void update(float dt) override;
    };
} // namespace Weapon


#endif //__GRENADE_H__
