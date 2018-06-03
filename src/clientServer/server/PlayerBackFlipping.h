/*
 *  Created by Rodrigo.
 *  date: 21/05/18
 */

#ifndef __PLAYER_BACK_FLIPPING_H__
#define __PLAYER_BACK_FLIPPING_H__

#include "PlayerState.h"

namespace Worms {
class BackFlipping : public State {
   public:
    BackFlipping();
    ~BackFlipping() = default;
    void update(Player &p, float dt, b2Body *body) override;
    void moveRight(Player &p) override;
    void moveLeft(Player &p) override;
    void jump(Player &p) override;
    void backFlip(Player &p) override;
    void stopMove(Player &p) override;

    void bazooka(Player &p) override;
    void grenade(Player &p) override;
    void cluster(Player &p) override;
    void mortar(Player &p) override;
    void banana(Player &p) override;

    void startShot(Player &p) override;
    void endShot(Player &p) override;
    void pointUp(Player &p) override;
    void pointDown(Player &p) override;
};
}  // namespace Worms

#endif  //__PLAYER_BACK_FLIPPING_H__
