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
    void endShot() override;
    void setTimeout(uint8_t time) override;
    std::list<Worms::Bullet> onExplode(const Worms::Bullet &mainBullet, Worms::Physics &physics) override;

   private:
    const Game::Weapon::Config &fragmentConfig;
    float powerChargeTime{0.0f};
};
}  // namespace Weapon

#endif  //__Cluster_H__
