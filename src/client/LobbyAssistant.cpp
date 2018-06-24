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
#include "ConnectionWindow.h"

GUI::LobbyAssistant::LobbyAssistant(ClientSocket &socket, Window &window) :
        window(window),
        font("assets/fonts/gruen_lemonograf.ttf", 28),
        cam(window, this->scale),
        communicationProtocol(socket, &output, &serverStream) {
    this->gameWindow = std::shared_ptr<GameWindow>(new ConnectionWindow{this->window, this->font, this->cam});
    this->gameWindow->addObserver(this);
//    this->gameWindow = std::shared_ptr<GameWindow>(new SelectActionWindow{this->window, this->font, this->cam});
//    this->gameWindow->addObserver(this);
}

void GUI::LobbyAssistant::run() {
    this->communicationProtocol.start();
    while (!this->quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT: {
                    this->quit = true;
                    throw;
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

//        this->clearScreen();
//        this->printCommands();
//        std::cin >> this->command;
//        this->command -= 48; //TODO encapsulate this
//        switch (this->command) {
//            case COMMAND_CREATE_GAME: {
//                this->createGame();
//                break;
//            }
//            case COMMAND_JOIN_GAME: {
//                this->joinGame();
//                break;
//            }
//        }
    }
}



void GUI::LobbyAssistant::onNotify(Subject &subject, Event event) {
    switch (event) {
        case Event::CreateGame: {
            this->output << IO::ClientGUIMsg{IO::ClientGUIInput::startCreateGame};
            break;
        }
        case Event::LevelSelected: {
            auto createGamesWindow = dynamic_cast<CreateGameWindow *>(this->gameWindow.get());
            this->output << IO::LevelSelected{IO::ClientGUIInput::levelSelected, createGamesWindow->buttonSelected};
            this->nextGameWindow = std::shared_ptr<GameWindow>(new WaitingPlayersWindow{this->window,
                                                                                    this->font,
                                                                                    this->cam,
                                                                                    createGamesWindow->levelsInfo[createGamesWindow->buttonSelected].playersQuantity});
            this->nextGameWindow->addObserver(this);
            break;
        }
        case Event::JoinGame: {
            this->output << IO::ClientGUIMsg{IO::ClientGUIInput::joinGame};
            this->nextGameWindow = std::shared_ptr<GameWindow>(new WaitingPlayersWindow{this->window,
                                                                                    this->font,
                                                                                    this->cam,
                                                                                    0});
            this->nextGameWindow->addObserver(this);
            break;
        }
        default: {
            break;
        }
    }
}

ClientSocket GUI::LobbyAssistant::getSocket() {
//    ClientSocket socket(std::move(this->communicationProtocol.getSocket()));
    this->communicationProtocol.stop();
    this->communicationProtocol.join();
    return /*std::move(socket);//*/std::move(this->communicationProtocol.getSocket());
}

void GUI::LobbyAssistant::handleServerResponse(IO::ServerResponse &response) {
    switch (response.action) {
        case IO::ServerResponseAction::startGame: {
            this->output << IO::ClientGUIMsg{IO::ClientGUIInput::quit};
            this->quit = true;
            break;
        }
        case IO::ServerResponseAction::levelsInfo: {
            this->nextGameWindow = std::shared_ptr<GameWindow>(new CreateGameWindow{this->window,
                                                                                this->font,
                                                                                this->cam ,
                                                                                this->communicationProtocol.levelsInfo});
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
