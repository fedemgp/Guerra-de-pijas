/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL2/SDL.h>

#include "Camera.h"
#include "Color.h"
#include "Exception.h"
#include "Texture.h"

namespace GUI {
class Animation {
   public:
    Animation(const Texture &texture);
    Animation(const Texture &texture, bool playReversed);
    Animation(const Texture &texture, bool playReversed, int initialFrame, bool autoUpdate);
    ~Animation();
    void update(float dt);
    void render(Position &p, Camera &cam, const SDL_RendererFlip &flipType);
    void reset();
    void advanceFrame();
    /**
     * Sets frame manually. Commonly used when the worm is aiming with a weapon
     * @param frame
     */
    void setFrame(int frame);
    void setFlip(SDL_RendererFlip flipType);
    SDL_RendererFlip getFlip();

    void setAnimateOnce();
    bool finished();

   private:
    /** SDL texture of the raw image. */
    const Texture *texture;
    /**
     * Disable Automatic update (when worm uses a bazooka, the frame changes
     * when user presses up or down)
     */
    bool autoUpdate{true};
    /** Current animation frame. */
    int currentFrame{0};
    /** Total number of frames in the sprite. */
    int numFrames;
    /** Size of the sprite (height and width). */
    int size;
    /** Time elapsed since last update. */
    float elapsed{0.0f};
    /** Frames per seconds (should this be elsewere?). */
    float frameRate{1.0f / 25.0f};
    SDL_RendererFlip flipType{SDL_FLIP_NONE};
    /** If true, when the animation finishes, it's played reversed instead of restarting. */
    bool playReversed{false};
    /** If true, plays the animation once. */
    bool playOnce{false};
    /** Frame step. */
    int step{1};
    bool animationFinished{false};
};
}  // namespace GUI

#endif  //__ANIMATION_H__
