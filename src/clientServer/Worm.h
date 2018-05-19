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
    /**
     * Fundamental class of the game, it is in charge of handling the user's
     * entries, and delegate in their attributes the rendering and animation
     */
   public:
    Direction direction;

    explicit Worm(const TextureManager &texture_mgr);
    ~Worm() {}
    /**
     * Calls State::update to change frame of animation
     * @param dt
     */
    void update(float dt);
    /**renderizar el gusano
     * Render worm in position (x,y)
     * @param x
     * @param y
     */
    void render(int x, int y, SDL_Renderer &renderer);
    /**
     * Using a state pattern, change its state depending on the input, and
     * sends it to the server
     * @param key
     * @param out
     */
    void handleKeyDown(SDL_Keycode key, IO::Stream<IO::PlayerInput> *out);
    /**
     * Same as handleKeyDown, but stops its current status.
     * @param key
     * @param out
     */
    void handleKeyUp(SDL_Keycode key, IO::Stream<IO::PlayerInput> *out);

    GUI::Animation getAnimation(StateID state) const;

    /**
     * Attributte that implements state pattern to change the behavior
     * of the class polymorphically.
     */
    void setState(StateID state);

   private:
    const TextureManager &texture_mgr;
    std::shared_ptr<State> state;
    GUI::Animation animation;
};
}  // namespace Worm

#endif  //__Worm__H__
