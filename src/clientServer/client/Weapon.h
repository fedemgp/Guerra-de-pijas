/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 27/05/18
 */

#ifndef __Weapon_H__
#define __Weapon_H__

#include <list>

#include "Animation.h"
#include "Camera.h"
#include "GameStateMsg.h"
#include "GameTextures.h"
#include "TextureManager.h"

#define BAZOOKA_CENTER_FRAME 16
#define GRENADE_CENTER_FRAME 15
#define BANANA_CENTER_FRAME 14
#define ANGLE_STEP 5.625f

namespace Worm {
class Weapon {
   public:
    explicit Weapon(const GUI::GameTextureManager &tex);
    ~Weapon() = default;
    /**
     * updates all its animations.
     * @param dt
     */
    void update(float dt);
    /**
     * renders all its animations.
     * @param p
     * @param cam
     * @param flip
     */
    void render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip);
    /**
     * changes its animations depending on the weapon to use.
     * @param id
     */
    void setWeapon(const WeaponID &id);
    const WeaponID &getWeaponID() const;
    /**
     * updates animations' frame depending on the angle.
     * @param angle
     */
    void setAngle(float angle);

   private:
    const GUI::GameTextureManager &textureMgr;
    WeaponID current{WeaponID::WNone};
    /**
     * list of animations, it may include the worm with the weapon, the scope
     * and the power animation
     */
    std::list<GUI::Animation> animations;
    GUI::Animation *weaponAnimation{nullptr};
    uint16_t centerFrame{BAZOOKA_CENTER_FRAME};
};
}  // namespace Weapon

#endif  //__Weapon_H__
