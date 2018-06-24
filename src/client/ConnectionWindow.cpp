//
// Created by rodrigo on 24/06/18.
//

#include "ConnectionWindow.h"

GUI::ConnectionWindow::ConnectionWindow(GUI::Window &window, GUI::Font &font, GUI::Camera &cam) :
        GameWindow(window, font, cam) {
    std::string msg(CONNECT_MSG);
    this->buttons.emplace_back(msg, this->font, SDL_Color{0xFF, 0xFF, 0xFF}, this->textSize);
    int x = this->window.getWidth() / 2;
    int y = this->window.getHeight() * 3 / 4;
    this->buttons.back().position = ScreenPosition{x, y};
    this->buttons.back().height = this->textSize * 3 / 2;
    this->buttons.back().width = this->buttons.back().msg.size() * 20 + 20;

    x = this->window.getWidth() * 6 / 10;
    y = this->window.getHeight() * 2 / 7;
    int textFieldHeight = this->textSize * 3 / 2;
    int textFieldWidth = 400;
    std::string emptyMsg(" ");
    this->textFields.emplace_back(emptyMsg, ScreenPosition{x, y}, textFieldHeight, textFieldWidth, this->font);
    y = this->window.getHeight() * 4 / 7;
    emptyMsg = " ";
    this->textFields.emplace_back(emptyMsg, ScreenPosition{x, y}, textFieldHeight, textFieldWidth, this->font);
}

void GUI::ConnectionWindow::start() {

}

void GUI::ConnectionWindow::render() {
    this->window.clear(SDL_Color{0xFF, 0xFF, 0xFF});

    SDL_Color black{0, 0, 0};

    Text ip{this->font};
    Text port{this->font};
    port.setBackground(black);
    int x = this->window.getWidth() * 3 / 10;
    int y = this->window.getHeight() * 2 / 7;
    ip.set("IP:", black, 50);
    ip.renderFixed(ScreenPosition{x, y - 50}, this->cam);
    y = this->window.getHeight() * 4 / 7;
    ip.set("Server port:", black, 50);
    ip.renderFixed(ScreenPosition{x, y - 50}, this->cam);

    for (auto &button : this->buttons) {
        button.render(this->cam);
    }

    for (auto &textField : this->textFields) {
        textField.render(this->cam);
    }

    this->window.render();
}

void GUI::ConnectionWindow::buttonPressed(GUI::ScreenPosition sp) {
    for (auto &textField : this->textFields) {
        textField.selected(sp);
    }
}

void GUI::ConnectionWindow::appendCharacter(char *text) {
    for (auto &textField : this->textFields) {
        if (textField.focus) {
            textField.appendCharacter(text);
        }
    }
}
