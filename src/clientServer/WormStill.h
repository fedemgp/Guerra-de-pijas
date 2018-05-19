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
    Still(GUI::Animation &&animation);
    ~Still();

    virtual void render(int x, int y, SDL_Renderer &renderer) override;
    virtual void update(float dt) override;

    virtual IO::PlayerInput moveRight(Worm &w) override;
    virtual IO::PlayerInput moveLeft(Worm &w) override;
    virtual IO::PlayerInput stopMove(Worm &w) override;

   private:
    GUI::Animation animation;
};
}  // namespace Worm

#endif  //__WORM_QUIET_H__
