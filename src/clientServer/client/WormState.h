/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __WORM_STATE_H__
#define __WORM_STATE_H__

#include "Animation.h"
#include "GameStateMsg.h"

namespace Worm {

class Worm;
/**
 * Worm status interface. It is used to implement the state pattern and
 * thus obtain a polymorphic behavior and at the same time treat the
 * animation as a state machine
 */
class State {
   public:
    State(StateID stateID) : stateID(stateID){};
    virtual ~State() = default;

    virtual void update(float dt) = 0;

    virtual IO::PlayerInput moveRight(Worm &w) = 0;
    virtual IO::PlayerInput moveLeft(Worm &w) = 0;
    virtual IO::PlayerInput stopMove(Worm &w) = 0;
    virtual IO::PlayerInput pointUp(Worm &w) = 0;
    virtual IO::PlayerInput pointDown(Worm &w) = 0;
    virtual IO::PlayerInput jump(Worm &w) = 0;
    virtual IO::PlayerInput bazooka(Worm &w) = 0;
    virtual IO::PlayerInput startShot(Worm &w) = 0;
    virtual IO::PlayerInput endShot(Worm &w) = 0;
    virtual IO::PlayerInput backFlip(Worm &w) = 0;
    //        virtual IO::PlayerInput fire(Worm &w) = 0;
    virtual StateID &getState() {
        return this->stateID;
    };

   protected:
    StateID stateID;
};
}  // namespace Worm

#endif  //__WORM_STATE_H__
