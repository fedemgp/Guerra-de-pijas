//
// Created by rodrigo on 23/06/18.
//

#include <iostream>
#include "GameStateMsg.h"
#include "CreateGameWindow.h"

GUI::CreateGameWindow::CreateGameWindow(GUI::Window &window, GUI::Font &font, GUI::Camera &cam,
                                        std::vector<IO::LevelInfo> &levelsInfo) :
        GameWindow(window, font, cam),
        levelsInfo(levelsInfo) {
    int height = this->levelInfoSize * 3 / 2;
    std::string msg(SELECT_LEVEL_MSG);
    int x = this->window.getWidth() / 2;
    int y = this->window.getHeight() * 3 / 4;
    this->buttons.emplace_back(msg, this->font, SDL_Color{0xFF, 0xFF, 0xFF}, this->levelInfoSize);
    this->buttons.back().position = ScreenPosition{x, y};
    this->buttons.back().height = height;
    this->buttons.back().width = msg.size() * 9 + 20;
    msg = NEXT_LEVEL_MSG;
    x = this->window.getWidth() * 3 / 4;
    y = this->window.getHeight() / 2;
    this->buttons.emplace_back(msg, this->font, SDL_Color{0xFF, 0xFF, 0xFF}, this->levelInfoSize);
    this->buttons.back().position = ScreenPosition{x, y};
    this->buttons.back().height = height;
    this->buttons.back().width = msg.size() * 9 + 20;
    msg = PREVIOUS_LEVEL_MSG;
    x = this->window.getWidth() / 4;
    y = this->window.getHeight() / 2;
    this->buttons.emplace_back(msg, this->font, SDL_Color{0xFF, 0xFF, 0xFF}, this->levelInfoSize);
    this->buttons.back().position = ScreenPosition{x, y};
    this->buttons.back().height = height;
    this->buttons.back().width = msg.size() * 9 + 20;
}

void GUI::CreateGameWindow::start() {

}

void GUI::CreateGameWindow::render() {
//    for (auto & levelInfo : this->levelsInfo) {
//        std::cout << levelInfo.name << " " << (int) levelInfo.playersQuantity << std::endl;
//    }
    this->window.clear(SDL_Color{0xFF, 0xFF, 0xFF});

    SDL_Color white{0xFF, 0xFF, 0xFF};
    SDL_Color black{0, 0, 0};

    Text levelName{this->font};
    Text levelPlayersQuantity{this->font};
    levelName.setBackground(black);
    levelPlayersQuantity.setBackground(black);
    int x = this->window.getWidth() * 4 / 10;
    int y = this->window.getHeight() * 3 / 7;
    levelName.set(LEVEL_MSG, white, 50);
    levelName.renderFixed(ScreenPosition{x, y - 50}, this->cam);
    x = this->window.getWidth() * 6 / 10;
    levelName.set(PLAYERS_MSG, white, 50);
    levelName.renderFixed(ScreenPosition{x, y - 50}, this->cam);
    levelName.setBackground(white);
    levelPlayersQuantity.setBackground(white);
    x = this->window.getWidth() * 4 / 10;
    y = this->window.getHeight() / 2;
    levelName.set(this->levelsInfo[this->buttonSelected].name, black, this->levelInfoSize);
    levelName.renderFixed(ScreenPosition{x, y}, this->cam);
    x = this->window.getWidth() * 6 / 10;
    levelName.set(std::to_string(this->levelsInfo[this->buttonSelected].playersQuantity), black, this->levelInfoSize);
    levelName.renderFixed(ScreenPosition{x, y}, this->cam);

    for (auto &button : this->buttons) {
        button.render(this->cam, this->window);
    }

    this->window.render();
}

void GUI::CreateGameWindow::buttonPressed(GUI::ScreenPosition sp) {
    if (this->buttons[0].inside(sp)) {
        this->notify(*this, Event::LevelSelected);
    }

    if (this->buttons[1].inside(sp)) {
        if (this->buttonSelected < this->levelsInfo.size() - 1) {
            this->buttonSelected++;
        }
    }

    if (this->buttons[2].inside(sp)) {
        if (this->buttonSelected > 0) {
            this->buttonSelected--;
        }
    }
}
