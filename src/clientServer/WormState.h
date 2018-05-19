/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __WORM_STATE_H__
#define __WORM_STATE_H__

#include "Animation.h"

namespace Worm {
enum class StateID { walk, quiet };

class Worm;
class State {
   public:
    virtual ~State() = default;
    virtual void render(int x, int y, SDL_Renderer &renderer) = 0;
    virtual void update(double dt) = 0;
    virtual IO::PlayerInput moveRight(Worm &w) = 0;
    virtual IO::PlayerInput moveLeft(Worm &w) = 0;
    virtual IO::PlayerInput stopMove(Worm &w) = 0;
    //        virtual IO::PlayerInput pointUp(Worm &w) = 0;
    //        virtual IO::PlayerInput pointDown(Worm &w) = 0;
    //        virtual IO::PlayerInput jump(Worm &w) = 0;
    //        virtual IO::PlayerInput fire(Worm &w) = 0;
};
}  // namespace Worm

#endif  //__WORM_STATE_H__
