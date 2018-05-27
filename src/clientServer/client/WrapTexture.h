#ifndef WRAP_TEXTURE_H_
#define WRAP_TEXTURE_H_

#include "Camera.h"
#include "client/Texture.h"

namespace GUI {
class WrapTexture {
   public:
    WrapTexture(const Texture &texture, int width, int height);
    ~WrapTexture();

    void render(Position p, Camera &camera);

   private:
    const Texture &texture;
    int width, height;
};
}  // namespace GUI

#endif
