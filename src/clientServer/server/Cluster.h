/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#ifndef __Cluster_H__
#define __Cluster_H__

#include "Physics.h"
#include "Player.h"
#include "Weapon.h"

namespace Weapon {
class Cluster : public Worms::Weapon {
   public:
    Cluster(float angle);
    ~Cluster() override = default;
    void update(float dt) override;
    void startShot() override;
    void endShot(Worms::Player &p, Worms::Physics &physics) override;

    uint16_t timeLimit{5};
};
}  // namespace Weapon

#endif  //__Cluster_H__
