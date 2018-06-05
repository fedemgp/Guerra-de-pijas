/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#ifndef __GRENADE_H__
#define __GRENADE_H__

#include "Weapon.h"

namespace Weapon {
class Grenade : public Worms::Weapon {
   public:
    Grenade(float angle);
    ~Grenade() override = default;
    void update(float dt) override;
    void startShot() override;
    void endShot(Worms::Player &p, Worms::Physics &physics) override;
    void setTimeout(uint8_t time) override;

   private:
    uint16_t timeLimit{5};
    float powerChargeTime{0.0f};
};
}  // namespace Weapon

#endif  //__GRENADE_H__
