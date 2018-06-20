#ifndef WRAP_TEXTURE_H_
#define WRAP_TEXTURE_H_

#include "Camera.h"
#include "Texture.h"

namespace GUI {
class WrapTexture {
   public:
    WrapTexture(const Texture &texture, float width, float height);
    ~WrapTexture();

    void render(Position p, Camera &camera);
    void render(Position p, float angle, Camera &camera);
    void renderFixed(ScreenPosition p, Camera& camera);

   private:
    const Texture &texture;
    float width, height;
};
}  // namespace GUI

#endif
