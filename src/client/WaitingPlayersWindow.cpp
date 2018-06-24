//
// Created by rodrigo on 24/06/18.
//

#include "WaitingPlayersWindow.h"

GUI::WaitingPlayersWindow::WaitingPlayersWindow(GUI::Window &window, GUI::Font &font, GUI::Camera &cam, unsigned int playersQuantity) :
        GameWindow(window, font, cam),
        playersQuantity(playersQuantity) {
}

void GUI::WaitingPlayersWindow::start() {

}

void GUI::WaitingPlayersWindow::render() {
    this->window.clear(SDL_Color{0xFF, 0xFF, 0xFF});
    
    Text playersConnected{this->font};
    int x = this->window.getWidth() * 2 / 5;
    int y = this->window.getHeight() / 2;
    playersConnected.set("Players connected", SDL_Color{0, 0, 0}, 50);
    playersConnected.renderFixed(ScreenPosition{x, y}, this->cam);
    x = this->window.getWidth() * 3 / 5;
    y = this->window.getHeight() / 2;
    playersConnected.setBackground(SDL_Color{0, 0, 0});
    playersConnected.set(std::to_string(this->playersConnected) + "/" + std::to_string(this->playersQuantity), SDL_Color{0xFF, 0xFF, 0xFF}, 50);
    playersConnected.renderFixed(ScreenPosition{x, y}, this->cam);

    this->window.render();
}

void GUI::WaitingPlayersWindow::buttonPressed(GUI::ScreenPosition sp) {

}

void GUI::WaitingPlayersWindow::appendCharacter(char *text) {

}
