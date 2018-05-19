/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __Worm_H__
#define __Worm_H__

#include "Animation.h"
#include "GameStateMsg.h"
#include "Stream.h"
#include "WormState.h"

namespace Worm {
class Worm {
   public:
    explicit Worm(SDL_Renderer &renderer);
    ~Worm() = default;
    void update(double dt);
    void render(int x, int y);
    void handleKeyDown(SDL_Keycode key, IO::Stream<IO::PlayerInput> *out);
    void handleKeyUp(SDL_Keycode key, IO::Stream<IO::PlayerInput> *out);
    std::shared_ptr<State> state;

   private:
    SDL_Renderer &renderer;
};
}  // namespace Worm

#endif  //__Worm__H__
