//
// Created by rodrigo on 3/06/18.
//

#ifndef INC_4_WORMS_LAND_H
#define INC_4_WORMS_LAND_H

#include <cstdint>
#include "PlayerState.h"

namespace Worms {
class Land : public State {
   public:
    Land();
    ~Land() = default;
    void update(Player &p, float dt, b2Body *body) override;
    void moveRight(Player &p) override;
    void moveLeft(Player &p) override;
    void jump(Player &p) override;
    void backFlip(Player &p) override;
    void stopMove(Player &p) override;
    void setTimeout(Player &p, uint8_t time) override;

    void bazooka(Player &p) override;
    void grenade(Player &p) override;
    void cluster(Player &p) override;
    void mortar(Player &p) override;
    void banana(Player &p) override;
    void holy(Player &p) override;
    void aerialAttack(Player &p) override;
    void dynamite(Player &p) override;
    void baseballBat(Player &p) override;
    void teleport(Player &p) override;

    void startShot(Player &p) override;
    void endShot(Player &p) override;
    void pointUp(Player &p) override;
    void pointDown(Player &p) override;

   private:
    float timeElapsed{0.0f};
    float landTime;
};
}  // namespace Worms

#endif  // INC_4_WORMS_LAND_H
