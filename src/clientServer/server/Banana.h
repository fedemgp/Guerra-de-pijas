/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#ifndef __Banana_H__
#define __Banana_H__


#include "Weapon.h"

namespace Weapon{
class Banana: public Worms::Weapon{
public:
    Banana(float angle);
    ~Banana() override = default;
    void update(float dt) override;
    void startShot() override;
    void endShot(Worms::Player &p, Worms::Physics &physics) override;

private:
    uint16_t timeLimit{5};
};
} // namespace Weapon


#endif //__Banana_H__