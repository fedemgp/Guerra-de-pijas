/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __WORM_WALK_LEFT_H__
#define __WORM_WALK_LEFT_H__

#include <SDL2/SDL_system.h>

#include "GameStateMsg.h"
#include "Worm.h"
#include "WormState.h"

namespace Worm {
class WalkLeft : public State {
   public:
    explicit WalkLeft(SDL_Renderer &r);
    ~WalkLeft();
    void render(int x, int y) override;
    void update(double dt) override;
    IO::PlayerInput moveRight(Worm &w) override;
    IO::PlayerInput moveLeft(Worm &w) override;
    IO::PlayerInput stopMove(Worm &w) override;

   private:
    GUI::Animation animation;
    SDL_Renderer &renderer;
};
}  // namespace Worm

#endif  //__WORM_WALK_LEFT_H__
