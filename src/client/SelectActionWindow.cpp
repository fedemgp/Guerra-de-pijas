//
// Created by rodrigo on 19/06/18.
//

#include <SDL2/SDL.h>

#include "SelectActionWindow.h"
#include "Text.h"
#include "Window.h"

GUI::SelectActionWindow::SelectActionWindow(GUI::Window &window) :
        GameWindow (window) {
}

void GUI::SelectActionWindow::start() {
    while (!this->quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT: {
                    this->quit = true;
                    break;
                }
                case SDL_KEYDOWN: {
                    break;
                }
                case SDL_KEYUP: {
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
//                    GUI::Position global = this->cam.screenToGlobal(GUI::ScreenPosition{x, y});
//                    cur.mouseButtonDown(global, &this->output);
                }
            }
        }
    }
}

void GUI::SelectActionWindow::render() {

}
