//
// Created by rodrigo on 21/05/18.
//

#ifndef __PLAYER_BAZOOKA_H__
#define __PLAYER_BAZOOKA_H__

#include "PlayerState.h"

#define MAX_SHOT_POWER 50

namespace Worms {
class Bazooka : public State {
   public:
    Bazooka();
    ~Bazooka() = default;
    void update(Player &p, float dt, b2Body *body) override;
    void moveRight(Player &p) override;
    void moveLeft(Player &p) override;
    void jump(Player &p) override;
    void bazooka(Player &p) override;
    void startShot(Player &p) override;
    void endShot(Player &p) override;
    void stopMove(Player &p) override;
    void pointUp(Player &p) override;
    void pointDown(Player &p) override;
    void backFlip(Player &p) override;

   private:
    bool increaseShotPower{false};
    int shotPower{0};
};
}  // namespace Worms

#endif  //__PLAYER_BAZOOKA_H__
