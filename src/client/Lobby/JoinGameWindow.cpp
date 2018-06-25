#include "JoinGameWindow.h"

const SDL_Color WHITE = {0xff, 0xff, 0xff};
const SDL_Color BLACK = {0, 0, 0};

const int TEXT_SIZE = 40;

GUI::JoinGameWindow::JoinGameWindow(Window &window, Font &font, Camera &cam,
                                    std::vector<IO::GameInfo> &info)
    : GameWindow(window, font, cam),
      gameName(font),
      numPlayers(font),
      prev("previous", font),
      next("next", font),
      info(info) {
    this->prev.textColor = WHITE;
    this->prev.textSize = TEXT_SIZE;
    this->prev.setBackground(BLACK);

    this->next.textColor = WHITE;
    this->next.textSize = TEXT_SIZE;
    this->next.setBackground(BLACK);
}

/**
 * @brief Called when the window is started.
 *
 */
void GUI::JoinGameWindow::start() {}

/**
 * @brief Renders the window.
 *
 */
void GUI::JoinGameWindow::render() {
    this->window.clear(SDL_Color{0xFF, 0xFF, 0xFF});

    const ScreenPosition center{this->window.getWidth() / 2, this->window.getHeight() / 2};

    this->prev.position = {this->window.getWidth() / 4, this->window.getHeight() / 2};
    this->next.position = {this->window.getWidth() * 3 / 4, this->window.getHeight() / 2};

    this->prev.render(this->cam);
    this->next.render(this->cam);

    if (this->info.size() > 0) {
        const IO::GameInfo &info = this->info.at(this->currentGameIndex);

        this->gameName.set("Game #" + std::to_string(info.gameID), BLACK, TEXT_SIZE * 2);
        this->gameName.renderFixed(center - ScreenPosition{0, this->window.getHeight() / 4},
                                   this->cam);

        std::string msg =
            std::to_string(info.numCurrentPlayers) + "/" + std::to_string(info.numTotalPlayers);
        this->numPlayers.set(msg, BLACK, TEXT_SIZE * 2);
    }

    this->window.render();
}

/**
 * @brief Checks if a button was pressed.
 *
 * @param sp Position where there was a click.
 */
void GUI::JoinGameWindow::buttonPressed(ScreenPosition sp) {
    if (this->prev.inside(sp)) {
        if (this->currentGameIndex == 0) {
            this->currentGameIndex = static_cast<uint8_t>(this->info.size()) - 1;
        } else {
            this->currentGameIndex--;
        }
    } else if (this->prev.inside(sp)) {
        this->currentGameIndex = (this->currentGameIndex + 1) % this->info.size();
    }
}

/**
 * @brief Handles key press events.
 *
 * @param key Key pressed.
 */
void GUI::JoinGameWindow::handleKeyDown(SDL_Keycode key) {}

void GUI::JoinGameWindow::appendCharacter(char text[32]) {}
