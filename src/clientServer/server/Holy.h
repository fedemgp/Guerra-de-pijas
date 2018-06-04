/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#ifndef __Holy_H__
#define __Holy_H__


#include "Weapon.h"

namespace Weapon{
class Holy: public Worms::Weapon{
public:
    Holy(float angle);
    ~Holy() override = default;
    void update(float dt) override;
    void startShot() override;
    void endShot(Worms::Player &p, Worms::Physics &physics) override;

private:
    uint16_t timeLimit{5};
};
} // namespace Weapon


#endif //__Holy_H__
