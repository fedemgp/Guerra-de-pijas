#ifndef _PLAYER_SLIDING_H
#define _PLAYER_SLIDING_H

#include "Config.h"
#include "PlayerState.h"

namespace Worms {
class Sliding : public State {
   public:
    Sliding();
    ~Sliding() = default;
    void update(Player &p, float dt, b2Body *body) override;
    void moveRight(Player &p) override;
    void moveLeft(Player &p) override;
    void jump(Player &p) override;
    void setTimeout(Player &p, uint8_t time) override;

    void bazooka(Player &p) override;
    void grenade(Player &p) override;
    void cluster(Player &p) override;
    void mortar(Player &p) override;
    void banana(Player &p) override;
    void holy(Player &p) override;

    void startShot(Player &p) override;
    void endShot(Player &p) override;
    void backFlip(Player &p) override;
    void stopMove(Player &p) override;
    virtual void pointUp(Player &p) override;
    virtual void pointDown(Player &p) override;

   private:
    float timeElapsed{0.0f};
};
}  // namespace Worms

#endif  //_PLAYER_SLIDING_H
