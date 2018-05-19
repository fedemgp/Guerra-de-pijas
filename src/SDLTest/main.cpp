#include <Exception.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <thread>
#include "View.h"

/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 13/05/18
 */
void _start() {
    try {
        View view;
        view.loadMedia();
        bool keepRuning = true;
        int fooX = 600;
        int fooY = 360;
        int frame = 0;
        double angle = 0;
        bool goingLeft = true;
        SDL_RendererFlip flipType = SDL_FLIP_NONE;

        const int framesQuantity = 16;
        Uint32 frameStart;
        float frameTime(0);
        float dt(0);
        float FPS = 1000.0f / framesQuantity;

        while (keepRuning) {
            frameStart = SDL_GetTicks();
            SDL_Event event;
            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    keepRuning = false;
                } else if (event.type == SDL_KEYDOWN) {
                    // Select surfaces based on key press
                    switch (event.key.keysym.sym) {
                        case SDLK_UP: {
                            angle += 10;
                            break;
                        }
                        case SDLK_DOWN: {
                            angle -= 10;
                            break;
                        }
                        case SDLK_LEFT: {
                            fooX -= 1;
                            if (!goingLeft) {
                                goingLeft = true;
                                flipType = SDL_FLIP_NONE;
                            }
                            break;
                        }
                        case SDLK_RIGHT: {
                            fooX += 1;
                            if (goingLeft) {
                                goingLeft = false;
                                flipType = SDL_FLIP_HORIZONTAL;
                            }
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
            // Clear screen
            SDL_SetRenderDrawColor(view.renderer, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderClear(view.renderer);

            SDL_Rect *currentClip = &view.spriteClips[frame % WORM_WALK_SPRITES_QUANTITY];
            view.fooTexture.render(fooX, fooY, view.renderer, currentClip, angle, nullptr,
                                   flipType);

            dt = (SDL_GetTicks() - frameStart);
            frameTime += dt;
            while (frameTime > FPS) {
                // Go to next frame
                ++frame;
                // Cycle animation
                if (frame >= WORM_WALK_SPRITES_QUANTITY) {
                    frame = 0;
                }
                frameTime -= FPS;
            }

            // Update screen
            SDL_RenderPresent(view.renderer);
        }
    } catch (...) {
        std::cerr << "ERROR" << std::endl;
    }
}
int main(int argc, const char *argv[]) {
    try {
        std::thread t = std::thread(&_start);
        t.join();

    } catch (Exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}