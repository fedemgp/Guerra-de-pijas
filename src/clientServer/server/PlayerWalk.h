#ifndef _PLAYERWALKLEFT_H
#define _PLAYERWALKLEFT_H

#include "PlayerState.h"
#include "Config.h"

namespace Worms {
class Walk : public State {
   public:
    Walk();
    ~Walk() = default;
    void update(Player &p, float dt, b2Body *body) override;
    void moveRight(Player &p) override;
    void moveLeft(Player &p) override;
    void jump(Player &p) override;

    void bazooka(Player &p) override;
    void grenade(Player &p) override;
    void cluster(Player &p) override;

    void startShot(Player &p) override;
    void endShot(Player &p) override;
    void backFlip(Player &p) override;
    void stopMove(Player &p) override;
    virtual void pointUp(Player &p) override;
    virtual void pointDown(Player &p) override;

private:
    const float walkVelocity;
};
}

#endif  //_PLAYERWALKLEFT_H
