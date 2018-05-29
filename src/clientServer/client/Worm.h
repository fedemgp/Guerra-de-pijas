/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __Worm_H__
#define __Worm_H__

#define BAZOOKA_CENTER_FRAME 16
#define FLY_CENTER_FRAME 16
#define ANGLE_STEP 5.625f

#include <SDL2/SDL.h>
#include <memory>
#include "Animation.h"
#include "Camera.h"
#include "GameStateMsg.h"
#include "GameTextures.h"
#include "Stream.h"
#include "Weapon.h"
#include "WormState.h"
#include "utils.h"

namespace Worm {
enum class Direction { right, left, up, down };
using ID = char;

class Worm {
    /**
     * Fundamental class of the game, it is in charge of handling the user's
     * entries, and delegate in their attributes the rendering and animation
     */
   public:
    Direction direction{Direction::left};
    float health{0};
    const ID id;

    explicit Worm(ID id, const GUI::GameTextureManager &texture_mgr);
    ~Worm() {}
    /**
     * Calls State::update to change frame of animation
     * @param dt
     */
    void update(float dt);
    /**
     * Render worm in position (x,y)
     * @param x
     * @param y
     */
    void render(GUI::Position &p, GUI::Camera &cam);
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
    StateID &getState() const;
    /**
     * Update the animation with weapons, depending on the
     * worm's angle.
     * @param angle
     */
    void setWeaponAngle(float angle);
    /**
     * Update the used weapon
     * @param id
     */
    void setWeapon(const WeaponID &id);
    const WeaponID &getWeaponID() const;

   private:
    const GUI::GameTextureManager &texture_mgr;
    std::shared_ptr<State> state{nullptr};
    GUI::Animation animation;
    Weapon weapon;
    bool active{false};
};
}  // namespace Worm

#endif  //__Worm__H__
