/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 17/06/18
 */

#include <iostream>
#include <GameStateMsg.h>
#include <SDL2/SDL.h>
#include <zconf.h>

#include "GameWindow.h"
#include "LobbyAssistant.h"
#include "Text.h"
#include "Window.h"
#include "SelectActionWindow.h"
#include "CreateGameWindow.h"
#include "WaitingPlayersWindow.h"
#include "Lobby/JoinGameWindow.h"
#include "ConnectionWindow.h"

GUI::LobbyAssistant::LobbyAssistant(Window &window) :
        window(window),
        font(std::string(ASSETS_PATH) + "/fonts/gruen_lemonograf.ttf", 28),
        cam(window, this->scale, 600, 600) {
    this->gameWindow = std::shared_ptr<GameWindow>(new ConnectionWindow{this->window, this->font, this->cam});
    this->gameWindow->addObserver(this);
}

void GUI::LobbyAssistant::run() {
    while (!this->quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT: {
                    this->quit = true;
                    this->exit = true;
                    break;
                }
                case SDL_KEYDOWN: {
                    this->gameWindow->handleKeyDown(e.key.keysym.sym);
                    break;
                }
                case SDL_KEYUP: {
                    break;
                }
                case SDL_TEXTINPUT: {
                    if(!((e.text.text[0] == 'c' || e.text.text[0] == 'C') && (e.text.text[0] == 'v' || e.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {
                        //Append character
                        this->gameWindow->appendCharacter(e.text.text);
                    }
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    GUI::Position global = this->cam.screenToGlobal(GUI::ScreenPosition{x, y});
                    this->gameWindow->buttonPressed(ScreenPosition{x, y});
                }
            }
        }

        IO::ServerResponse sr{};
        if (this->serverStream.pop(sr, false)) {
            this->handleServerResponse(sr);
        }

        if (this->nextGameWindow) {
            this->gameWindow = this->nextGameWindow;
            this->nextGameWindow = nullptr;
        }

        this->gameWindow->render();
        usleep(50 * 1000);
    }
}



void GUI::LobbyAssistant::onNotify(Subject &subject, Event event) {
    switch (event) {
        case Event::ConnectionToServer: {
            auto connectionWindow = dynamic_cast<ConnectionWindow *>(this->gameWindow.get());
            ConnectionInfo info = connectionWindow->getConnectionInfo();
            ClientSocket socket(info.ip, info.port);
            this->communicationProtocol = std::shared_ptr<IO::CommunicationProtocol>(
                    new IO::CommunicationProtocol(socket, &this->output, &this->serverStream));
            this->communicationProtocol->start();

            this->nextGameWindow = std::shared_ptr<GameWindow>(new SelectActionWindow{this->window, this->font, this->cam});
            this->nextGameWindow->addObserver(this);
            break;
        }
        case Event::CreateGame: {
            this->output << IO::ClientGUIMsg{IO::ClientGUIInput::startCreateGame};
            break;
        }
        case Event::LevelSelected: {
            auto createGameWindow = dynamic_cast<CreateGameWindow *>(this->gameWindow.get());
            this->communicationProtocol->levelToCreate = createGameWindow->buttonSelected;
            this->output << IO::ClientGUIMsg{IO::ClientGUIInput::levelSelected};
            this->nextGameWindow = std::shared_ptr<GameWindow>(new WaitingPlayersWindow{this->window,
                                                                                    this->font,
                                                                                    this->cam,
                                                                                    createGameWindow->levelsInfo[createGameWindow->buttonSelected].playersQuantity});
            this->nextGameWindow->addObserver(this);
            break;
        }
        case Event::JoinGame: {
            this->output << IO::ClientGUIMsg{IO::ClientGUIInput::startJoinGame};
            break;
        }
        case Event::LobbyToJoinSelected: {
            auto joinGameWindow = dynamic_cast<JoinGameWindow *>(this->gameWindow.get());
            this->communicationProtocol->gameToJoin = joinGameWindow->currentGameIndex;
            this->communicationProtocol->levelOfGameToJoin = joinGameWindow->info[joinGameWindow->currentGameIndex].levelID;
            this->output << IO::ClientGUIMsg{IO::ClientGUIInput::joinGame};
            this->nextGameWindow = std::shared_ptr<GameWindow>(new WaitingPlayersWindow{this->window,
                                                                                        this->font,
                                                                                        this->cam,
                                                                                        joinGameWindow->info[joinGameWindow->currentGameIndex].numTotalPlayers,
                                                                                        joinGameWindow->info[joinGameWindow->currentGameIndex].numCurrentPlayers});
            this->nextGameWindow->addObserver(this);
            break;
        }
        default: {
            break;
        }
    }
}

ClientSocket GUI::LobbyAssistant::getSocket() {
    return std::move(this->communicationProtocol->getSocket());
}

void GUI::LobbyAssistant::handleServerResponse(IO::ServerResponse &response) {
    switch (response.action) {
        case IO::ServerResponseAction::startGame: {
            this->levelPath = std::move(this->communicationProtocol->levelPath);
            this->backgroundPath = std::move(this->communicationProtocol->backgroundPath);
            this->output << IO::ClientGUIMsg{IO::ClientGUIInput::quit};
            this->quit = true;
            break;
        }
        case IO::ServerResponseAction::levelsInfo: {
            this->nextGameWindow = std::shared_ptr<GameWindow>(new CreateGameWindow{this->window,
                                                                                this->font,
                                                                                this->cam ,
                                                                                this->communicationProtocol->levelsInfo});
            this->nextGameWindow->addObserver(this);
            break;
        }
        case IO::ServerResponseAction::gamesInfo: {
            this->nextGameWindow = std::shared_ptr<GameWindow>(new JoinGameWindow{this->window,
                                                                                  this->font,
                                                                                  this->cam ,
                                                                                  this->communicationProtocol->gamesInfo});
            this->nextGameWindow->addObserver(this);
            break;
        }
        case IO::ServerResponseAction::playerConnected: {
            dynamic_cast<WaitingPlayersWindow *>(this->gameWindow.get())->playersConnected++;
            break;
        }
        default: {
            break;
        }
    }
}

GUI::Font & GUI::LobbyAssistant::getFont() {
    return this->font;
}

GUI::Camera & GUI::LobbyAssistant::getCam() {
    return this->cam;
}

GUI::LobbyAssistant::~LobbyAssistant() {
    this->output.close();
    this->serverStream.close();
    if (this->communicationProtocol != nullptr) {
        this->communicationProtocol->stop();
        this->communicationProtocol->join();
    }
}
