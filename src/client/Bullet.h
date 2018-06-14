/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#ifndef __Bullet_h__
#define __Bullet_h__

#include <GameStateMsg.h>
#include <memory>

#include "Animation.h"
#include "Explosion.h"
#include "GameSoundEffects.h"
#include "GameTextures.h"
#include "SoundEffectPlayer.h"

#define MISSILE_0_DEG_FRAME 8
#define MISSILE_ANGLE_STEP 11.25f

namespace Ammo {
class Bullet {
   public:
    explicit Bullet(const GUI::GameTextureManager &texture_mgr,
                    const GUI::GameSoundEffectManager &sound_effect_mgr, Worm::WeaponID id);
    ~Bullet() = default;
    void update(float dt);
    void render(GUI::Position p, GUI::Camera &cam);
    void setAngle(float angle);
    void setPosition(GUI::Position p);
    GUI::Position getPosition();
    void madeImpact();
    bool exploding();
    bool exploded();

   private:
    float angle{0};
    bool updateManually{true};
    const GUI::GameTextureManager &texture_mgr;
    const GUI::GameSoundEffectManager &sound_effect_mgr;
    GUI::Animation animation;
    GUI::Position position{0, 0};
    Worm::Explosion explosion;
    bool explode{false};
    Worm::WeaponID wid;
    std::shared_ptr<GUI::SoundEffectPlayer> soundEffectPlayer{nullptr};
};

struct ExplotionChekcer {
    bool operator()(std::shared_ptr<Bullet> &bullet) {
        return bullet->exploded();
    }
};
}

#endif  //__Bullet_H__
