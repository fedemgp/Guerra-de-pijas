#ifndef WATER_H_
#define WATER_H_

#include "Camera.h"
#include "GameTextures.h"

namespace GUI {
class Water {
   public:
    Water(const GameTextureManager &tm);
    ~Water() = default;

    void update(float dt);
    void render(Camera &camera);

   private:
    const GUI::GameTextureManager &textureManager;
    float elapsed{0};
    float yDelta{0};
};
}  // namespace GUI

#endif
