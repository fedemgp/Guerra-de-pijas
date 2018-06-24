/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __Worm_H__
#define __Worm_H__

#define FLY_CENTER_FRAME 16
#define DROWN_CENTER_FRAME 0
#define ANGLE_STEP 5.625f

#include <SDL2/SDL.h>
#include <memory>

#include "Animation.h"
#include "Camera.h"
#include "Direction.h"
#include "GameSoundEffects.h"
#include "GameStateMsg.h"
#include "GameTextures.h"
#include "SoundEffectPlayer.h"
#include "Stream.h"
#include "Weapons/Explosion.h"
#include "Weapons/Weapon.h"
#include "WormState/WormState.h"
#include "utils.h"

namespace Worm {
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

    explicit Worm(ID id, const GUI::GameTextureManager &texture_mgr,
                  const GUI::GameSoundEffectManager &sound_effect_mgr);
    ~Worm() {}
    /**
     * @brief Calls State::update to change frame of animation
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
     * @brief Using a state pattern, change its state depending on the input, and
     * sends it to the server
     * @param key
     * @param out
     */
    void handleKeyDown(SDL_Keycode key, IO::Stream<IO::PlayerMsg> *out);
    /**
     * @brief Same as handleKeyDown, but stops its current status.
     * @param key
     * @param out
     */
    void handleKeyUp(SDL_Keycode key, IO::Stream<IO::PlayerMsg> *out);
    /**
     * @brief Receives a position in global coordinates and sends it to the state
     * so it can handle it.
     * @param position
     */
    void mouseButtonDown(GUI::Position position, IO::Stream<IO::PlayerMsg> *pStream);
    GUI::Animation getAnimation(StateID state) const;
    /**
     * @brief Attributte that implements state pattern to change the behavior
     * of the class polymorphically.
     */
    void setState(StateID state);
    StateID &getState() const;
    /**
     * @brief Update the animation with weapons, depending on the
     * worm's angle.
     * @param angle
     */
    void setWeaponAngle(float angle);
    /**
     * @brief Update the used weapon
     * @param id
     */
    void setWeapon(const WeaponID &id);
    const WeaponID &getWeaponID() const;
    void setPosition(GUI::Position p);
    /**
     * @brief Starts the PowerBar's rendering, adding animations in its container
     */
    void startShot();
    /**
     * @brief End PowerBar's rendering, freeing its container
     */
    void endShot();
    /**
     * @brief resets some attributes when the turn ends
     */
    void reset();

   private:
    const GUI::GameTextureManager &texture_mgr;
    const GUI::GameSoundEffectManager &sound_effect_mgr;
    std::shared_ptr<State> state{nullptr};
    GUI::Animation animation;
    std::shared_ptr<Weapon> weapon{nullptr};
    bool active{false};
    GUI::Position position{0, 0};
    std::shared_ptr<Explosion> explosion{nullptr};
    bool hasFired{false};
    std::shared_ptr<GUI::SoundEffectPlayer> soundEffectPlayer{nullptr};
    void playSoundEffect(StateID state);
    void playWeaponSoundEffect(const WeaponID &id);
};
}  // namespace Worm

#endif  //__Worm__H__
