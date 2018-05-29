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
#define ANGLE_STEP 5.625f

namespace Worm{
class Weapon {
public:
    explicit Weapon(const GUI::GameTextureManager &tex);
    ~Weapon() = default;
    void update(float dt);
    void render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip);
    void setWeapon(const WeaponID &id);
    const WeaponID &getWeaponID()const;

private:
    const GUI::GameTextureManager &textureMgr;
    WeaponID current{WeaponID::WNone};
    /**
     * list of animations, it may include the worm with the weapon, the scope
     * and the power animation
     */
    std::list<GUI::Animation> animations;

};
} // namespace Weapon

#endif //__Weapon_H__
