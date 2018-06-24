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
    std::string msg(SELECT_LEVEL_MSG);
    int x = this->window.getWidth() * 7 / 8;
    int y = this->window.getHeight() / 5;
    for (size_t i = 0; i < this->levelsInfo.size(); i++) {
        this->buttons.emplace_back(msg, this->font, SDL_Color{0xFF, 0xFF, 0xFF}, this->levelInfoSize);
        this->buttons.back().position = ScreenPosition{x, y};
        this->buttons.back().height = this->levelInfoSize * 3 / 2;
        this->buttons.back().width = msg.size() * 9 + 20;
        y += this->levelInfoSize * 3 / 2;
    }
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
    int x = this->window.getWidth() * 3 / 10;
    int y = this->window.getHeight() / 5;
    levelName.set("Level", white, 50);
    levelName.renderFixed(ScreenPosition{x, y - 50}, this->cam);
    x = this->window.getWidth() * 7 / 10;
    levelName.set("Players", white, 50);
    levelName.renderFixed(ScreenPosition{x, y - 50}, this->cam);
    levelName.setBackground(white);
    levelPlayersQuantity.setBackground(white);
    for (auto &levelInfo : this->levelsInfo) {
        x = this->window.getWidth() * 3 / 10;
        levelName.set(levelInfo.name, black, this->levelInfoSize);
        levelName.renderFixed(ScreenPosition{x, y}, this->cam);
        x = this->window.getWidth() * 7 / 10;
        levelName.set(std::to_string(levelInfo.playersQuantity), black, this->levelInfoSize);
        levelName.renderFixed(ScreenPosition{x, y}, this->cam);
        y += this->levelInfoSize * 3 / 2;
    }
    for (auto &button : this->buttons) {
        button.render(this->cam, this->window);
    }

    this->window.render();
}

void GUI::CreateGameWindow::buttonPressed(GUI::ScreenPosition sp) {
    int i{0};
    for (auto &button : this->buttons) {
        if (button.inside(sp)) {
            this->buttonSelected = i;
            this->notify(*this, Event::LevelSelected);
        }
        i++;
    }
}
