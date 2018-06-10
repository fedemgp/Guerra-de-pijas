//
// Created by rodrigo on 2/06/18.
//

#ifndef INC_4_WORMS_EXPLOSION_H
#define INC_4_WORMS_EXPLOSION_H

#include <Animation.h>
#include <vector>
#include "GameTextures.h"

namespace Worm {
class Explosion {
   public:
    explicit Explosion(const GUI::GameTextureManager &texture_mgr);
    ~Explosion() = default;
    void update(float dt);
    void render(GUI::Camera &cam);
    GUI::Position position{0, 0};
    bool finished();

   private:
    const GUI::GameTextureManager &texture_mgr;
    std::vector<GUI::Animation> animations;
    bool explosionFinished{false};
};
}

#endif  // INC_4_WORMS_EXPLOSION_H
