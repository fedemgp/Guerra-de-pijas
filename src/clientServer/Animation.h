/*
 * Created by Federico Manuel Gomez Peter 
 * Date: 17/05/18.
 */

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL2/SDL.h>

#include "Color.h"
#include "Exception.h"

namespace GUI{
    class Animation {
    public:
        Animation(const std::string &filename, SDL_Renderer &renderer, Color key);
        ~Animation();
        void update(float dt);
        void render(SDL_Renderer &renderer, int x, int y);
        void advance_frame();
        void flip(SDL_RendererFlip flip_type);

    private:
        /** SDL texture of the raw image. */
        SDL_Texture *texture{nullptr};
        /** Current animation frame. */
        int current_frame{0};
        /** Total number of frames in the sprite. */
        int num_frames;
        /** Size of the sprite (height and width). */
        int size;
        /** Time elapsed since last update. */
        float elapsed;
        /** Frames per seconds (should this be elsewere?). */
        float frame_rate{1.0f / 30.0f};
        SDL_RendererFlip flip_type{SDL_FLIP_NONE};
    };
}//namespace GUI


#endif //__ANIMATION_H__
