#ifndef CAMERA_H_
#define CAMERA_H_

#include <SDL2/SDL.h>

#include "Point.h"
#include "Texture.h"
#include "Window.h"

namespace GUI {
using Position = Math::Point<float>;
using ScreenPosition = Math::Point<int>;

class Camera {
   public:
    Camera(GUI::Window &window, float scale, float width, float height);
    ~Camera();

    bool isMoving() const;

    void setTo(Position coords);
    void moveTo(Position coords);

    ScreenPosition globalToScreen(Position);
    Position screenToGlobal(ScreenPosition);

    float getScale() const;
    Position getPosition() const;
    SDL_Renderer &getRenderer() const;

    void draw(const Texture &texture, Position p);
    void draw(const Texture &texture, Position p, const SDL_Rect &clip);
    void draw(const Texture &texture, Position p, const SDL_Rect &clip, SDL_RendererFlip flip,
              float scale = 1);
    void drawLocal(const Texture &texture, ScreenPosition p);
    void drawLocal(const Texture &texture, ScreenPosition p, const SDL_Rect &clip);
    void drawLocal(const Texture &texture, ScreenPosition p, const SDL_Rect &clip,
                   SDL_RendererFlip flip, float scale = 1);
    void drawLocal(ScreenPosition p, const SDL_Rect &clip, SDL_Color color);

    Position clamp(Position p) const;

    void update(float dt);

   private:
    GUI::Window &window;
    /* current camera coordinates. */
    Position cur{0, 0};
    /* the position that the camera is moving towards to and the one that it started moving from. */
    Position start, dst;
    /* Distance scale factor. */
    float scale;
    /* elapsed time accumulator. */
    float elapsed{0};
    /* The SDL renderer. */
    SDL_Renderer &renderer;
    float width, height;
};
}  // namespace GUI

#endif
