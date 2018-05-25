#ifndef _PLAYERSTATE_H
#define _PLAYERSTATE_H

#include <Box2D/Common/b2Math.h>
#include <vector>
#include <Box2D/Dynamics/b2Body.h>

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
    virtual void bazooka(Player &p) = 0;
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
