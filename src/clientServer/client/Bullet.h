/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#ifndef __Bullet_H__
#define __Bullet_H__

#include "GameTextures.h"
#include "Animation.h"

#define MISSILE_0_DEG_FRAME 8
#define MISSILE_ANGLE_STEP 11.25f

namespace Ammo{
    class Bullet{
    public:
        explicit Bullet(const GUI::GameTextureManager &texture_mgr);
        ~Bullet() = default;
        void update(float dt);
        void render(int x, int y, SDL_Renderer &renderer);
        void setAngle(float angle);
    private:
        const GUI::GameTextureManager &texture_mgr;
        GUI::Animation animation;
    };

}

#endif //__Bullet_H__
