//
// Created by rodrigo on 19/06/18.
//

#include <SDL2/SDL.h>
#include <iostream>

#include "SelectActionWindow.h"
#include "Text.h"
#include "Window.h"

#define MSG_CREATE_GAME "Create game"
#define MSG_JOIN_GAME "Join game"

GUI::SelectActionWindow::SelectActionWindow(Window &window, Font &font, Camera &cam) :
        GameWindow(window, font, cam) {
    std::string msg(MSG_CREATE_GAME);
    this->buttons.emplace_back(ScreenPosition{this->window.getWidth() / 4, this->window.getHeight() / 2},
                               50, 300, msg, this->font);
    msg = MSG_JOIN_GAME;
    this->buttons.emplace_back(ScreenPosition{this->window.getWidth() * 3 / 4, this->window.getHeight() / 2},
                               50, 300, msg, this->font);
}

void GUI::SelectActionWindow::start() {

}

void GUI::SelectActionWindow::render() {
    this->window.clear(SDL_Color{0xFF, 0xFF, 0xFF});
    for (auto &button : this->buttons) {
        button.render(this->cam, this->window);
    }

    this->window.render();
}

void GUI::SelectActionWindow::buttonPressed(GUI::ScreenPosition sp) {
    if (this->buttons[0].inside(sp)) {
        std::cout<<"asdas\n";
//        this->notify(*this, Event::CreateGame);
    }
}
