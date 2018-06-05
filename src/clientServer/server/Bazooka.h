/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#ifndef __BAZOOKA_H__
#define __BAZOOKA_H__

#include "Weapon.h"

namespace Weapon {
class Bazooka : public Worms::Weapon {
   public:
    Bazooka(float angle);
    ~Bazooka() = default;
    void update(float dt) override;
    void startShot() override;
    void endShot(Worms::Player &p, Worms::Physics &physics) override;
    void setTimeout(uint8_t time) override;

   private:
    float powerChargeTime{0.0f};
};
}  // namespace Weapon

#endif  //__BAZOOKA_H__
