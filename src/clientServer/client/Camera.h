#ifndef CAMERA_H_
#define CAMERA_H_

#include <SDL2/SDL.h>

#include "Point.h"
#include "Texture.h"

namespace GUI {
using Position = Math::Point<float>;
using ScreenPosition = Math::Point<int>;

class Camera {
   public:
    Camera(float scale, int width, int height, SDL_Renderer &renderer);
    ~Camera();

    bool isMoving() const;

    void setTo(Position coords);
    void moveTo(Position coords);

    ScreenPosition globalToScreen(Position);

    SDL_Renderer &getRenderer() const;

    void draw(const Texture &texture, Position p);
    void draw(const Texture &texture, Position p, const SDL_Rect &clip);
    void draw(const Texture &texture, Position p, const SDL_Rect &clip, SDL_RendererFlip flip,
              float scale = 1);
    void drawLocal(const Texture &texture, ScreenPosition p);
    void drawLocal(const Texture &texture, ScreenPosition p, const SDL_Rect &clip);
    void drawLocal(const Texture &texture, ScreenPosition p, const SDL_Rect &clip,
                   SDL_RendererFlip flip, float scale = 1);

    void update(float dt);

   private:
    /* current camera coordinates. */
    Position cur{0, 0};
    /* the position that the camera is moving towards to and the one that it started moving from. */
    Position start, dst;
    /* Distance scale factor. */
    float scale;
    /* camera width and height. */
    int width, height;
    /* elapsed time accumulator. */
    float elapsed{0};
    /* The SDL renderer. */
    SDL_Renderer &renderer;
};
}  // namespace GUI

#endif
