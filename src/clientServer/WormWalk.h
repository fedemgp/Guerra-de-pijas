/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __WORM_WALK_H__
#define __WORM_WALK_H__

#include <SDL2/SDL_system.h>

#include "GameStateMsg.h"
#include "Worm.h"
#include "WormState.h"

namespace Worm {
class Walk : public State {
   public:
    explicit Walk(GUI::Animation &&animation);
    virtual ~Walk();

    virtual void render(int x, int y, SDL_Renderer &renderer) override;
    virtual void update(double dt) override;
    IO::PlayerInput moveRight(Worm &w) override;
    IO::PlayerInput moveLeft(Worm &w) override;
    IO::PlayerInput stopMove(Worm &w) override;

   private:
    GUI::Animation animation;
};
}  // namespace Worm

#endif  //__WORM_WALK_H__
