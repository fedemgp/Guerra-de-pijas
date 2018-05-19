/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __WORM_QUIET_H__
#define __WORM_QUIET_H__

#include <SDL2/SDL_system.h>

#include "GameStateMsg.h"
#include "Worm.h"
#include "WormState.h"

namespace Worm {
class Still : public State {
   public:
    Still(SDL_Renderer &r, SDL_RendererFlip flipType);
    ~Still();
    void render(int x, int y) override;
    void update(float dt) override;
    IO::PlayerInput moveRight(Worm &w) override;
    IO::PlayerInput moveLeft(Worm &w) override;
    IO::PlayerInput stopMove(Worm &w) override;

   private:
    GUI::Animation animation;
    SDL_Renderer &renderer;
};
}  // namespace Worm

#endif  //__WORM_QUIET_H__
