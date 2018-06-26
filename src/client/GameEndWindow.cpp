//
// Created by rodrigo on 26/06/18.
//

#include "GameEndWindow.h"

GUI::GameEndWindow::GameEndWindow(GUI::Window &window, GUI::Font &font, GUI::Camera &cam, bool youWin) :
        GameWindow(window, font, cam) {
    this->gameEndResultMsg = youWin ? "You Win!" : "You Lose!";
}

void GUI::GameEndWindow::start() {
    while (!this->quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT: {
                    this->quit = true;
//                    throw;
                    break;
                }
                default: {
                    break;
                }
            }
        }

        this->render();
    }
}

void GUI::GameEndWindow::render() {
    this->window.clear(SDL_Color{0xFF, 0xFF, 0xFF});

    SDL_Color black{0, 0, 0};

    Text gameResult{this->font};
    int x = this->window.getWidth() / 2;
    int y = this->window.getHeight() / 2;
    gameResult.set(this->gameEndResultMsg, black, 50);
    gameResult.renderFixed(ScreenPosition{x, y}, this->cam);

    this->window.render();
}

void GUI::GameEndWindow::buttonPressed(GUI::ScreenPosition sp) {
}

void GUI::GameEndWindow::appendCharacter(char *text) {
}

void GUI::GameEndWindow::handleKeyDown(SDL_Keycode key) {
}
