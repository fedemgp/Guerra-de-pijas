/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 27/05/18
 */

#ifndef __Weapon_H__
#define __Weapon_H__

#include "Animation.h"
#include "Camera.h"
#include "Direction.h"
#include "GameStateMsg.h"
#include "../GameTextures.h"
#include "TextureManager.h"

#define ANGLE_STEP 5.625f
#define SCOPE_DISTANCE 4

namespace Worm {
class Weapon {
   public:
    explicit Weapon(const GUI::GameTextureManager &texMgr, GUI::GameTextures tex,
                    uint16_t centerFrame, WeaponID id);
    virtual ~Weapon() = default;
    /**
     * updates all its animations.
     * @param dt
     */
    virtual void update(float dt) = 0;
    /**
     * renders all its animations.
     * @param p
     * @param cam
     * @param flip
     */
    virtual void render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) = 0;
    const WeaponID &getWeaponID() const;
    /**
     * updates animations' frame depending on the angle.
     * @param angle
     */
    virtual void setAngle(float angle, Direction d) = 0;
    /**
     * Starts the PowerBar's rendering, adding animations in its container
     */
    virtual void startShot() = 0;
    /**
     * End PowerBar's rendering, freeing its container
     */
    virtual void endShot() = 0;
    /**
     * When using remoteControl weapons, starts the animation of the worm
     * and return
     */
    virtual bool positionSelected() = 0;

   protected:
    const GUI::GameTextureManager &textureMgr;
    WeaponID current;
    uint16_t centerFrame;
    GUI::Animation weaponAnimation;
    float angle{0.0f};
};
}  // namespace Weapon

#endif  //__Weapon_H__
