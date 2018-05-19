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
    /**
     * Fundamental class of the game, it is in charge of handling the user's
     * entries, and delegate in their attributes the rendering and animation
     */
   public:
    explicit Worm(SDL_Renderer &renderer);
    ~Worm() = default;
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
    void render(int x, int y);
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
    /**
     * Attributte that implements state pattern to change the behavior
     * of the class polymorphically.
     */
    std::shared_ptr<State> state;

   private:
    SDL_Renderer &renderer;
};
}  // namespace Worm

#endif  //__Worm__H__
