/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __Worm_H__
#define __Worm_H__

#include <SDL2/SDL.h>
#include <memory>
#include "Animation.h"
#include "GameStateMsg.h"
#include "Stream.h"
#include "TextureManager.h"
#include "WormState.h"
#include "utils.h"

namespace Worm {
using TextureManager = GUI::TextureManager<StateID, Utils::EnumClassHash>;

enum class Direction { right, left };

class Worm {
   public:
    Direction direction;

    explicit Worm(const TextureManager &texture_mgr);
    ~Worm() = default;

    void update(double dt);
    void render(int x, int y, SDL_Renderer &renderer);
    void handleKeyDown(SDL_Keycode key, IO::Stream<IO::PlayerInput> *out);
    void handleKeyUp(SDL_Keycode key, IO::Stream<IO::PlayerInput> *out);

    GUI::Animation getAnimation(StateID state) const;
    void setState(StateID state);

   private:
    const TextureManager &texture_mgr;
    std::shared_ptr<State> state;
};
}  // namespace Worm

#endif  //__Worm__H__
