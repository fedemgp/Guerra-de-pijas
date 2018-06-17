#ifndef _PLAYERSTATE_H
#define _PLAYERSTATE_H

#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>
#include <vector>

#include "GameStateMsg.h"

namespace Worms {
class Player;
class State {
   public:
    explicit State(Worm::StateID id);
    virtual ~State() = default;
    virtual void update(Player &p, float dt, b2Body *body) = 0;
    virtual void moveRight(Player &p) = 0;
    virtual void moveLeft(Player &p) = 0;
    virtual void jump(Player &p) = 0;
    virtual void setTimeout(Player &p, uint8_t time) = 0;

    virtual void bazooka(Player &p) = 0;
    virtual void grenade(Player &p) = 0;
    virtual void cluster(Player &p) = 0;
    virtual void mortar(Player &p) = 0;
    virtual void banana(Player &p) = 0;
    virtual void holy(Player &p) = 0;
    virtual void aerialAttack(Player &p) = 0;
    virtual void dynamite(Player &p) = 0;
    virtual void teleport(Player &p) = 0;

    virtual void startShot(Player &p) = 0;
    virtual void endShot(Player &p) = 0;
    virtual void backFlip(Player &p) = 0;
    virtual void stopMove(Player &p) = 0;
    virtual void pointUp(Player &p) = 0;
    virtual void pointDown(Player &p) = 0;
    virtual Worm::StateID getState() const;

   protected:
    Worm::StateID stateID;
    std::vector<float> impulses{0.0f, 0.0f};
};
}

#endif  //_PLAYERSTATE_H
