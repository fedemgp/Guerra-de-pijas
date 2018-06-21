/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 17/06/18
 */

#include <iostream>
#include <GameStateMsg.h>
#include <SDL2/SDL.h>

#include "LobbyAssistant.h"
#include "Text.h"
#include "Window.h"
#include "SelectActionWindow.h"

GUI::LobbyAssistant::LobbyAssistant(ClientSocket &socket, Window &window) :
        protocol(socket),
        window(window),
        font("assets/fonts/gruen_lemonograf.ttf", 28),
        cam(window, this->scale) {
    this->gameWindow = std::shared_ptr<GameWindow>(new SelectActionWindow{this->window, this->font, this->cam});
}

void GUI::LobbyAssistant::run(){
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
                    break;
                }
                case SDL_KEYUP: {
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    GUI::Position global = this->cam.screenToGlobal(GUI::ScreenPosition{x, y});
                    this->gameWindow->buttonPressed(ScreenPosition{x, y}/*ScreenPosition{static_cast<int>(global.x), static_cast<int>(global.y)}*/);
                }
            }
        }
        this->gameWindow->render();

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

void GUI::LobbyAssistant::clearScreen(){
    std::cout << std::string(100, '\n');
}

void GUI::LobbyAssistant::printCommands() {
    std::cout << "Select option" << std::endl;
    std::cout << COMMAND_CREATE_GAME << " Create game." << std::endl
              << COMMAND_JOIN_GAME << " Shows current lobbies. Must select one." << std::endl;
}
//TODO notify to the main thread that player select this so it can render properly
void GUI::LobbyAssistant::createGame(){
    this->protocol << this->command;
    this->waitGameStart();
}

void GUI::LobbyAssistant::getGames(){
    this->command = COMMAND_GET_GAMES;
    this->protocol << this->command;
    std::vector<std::uint8_t> games;
    this->protocol >> games;
//    this->clearScreen();
    std::cout << "Lobby ID\t\tIn room\t\t\tTotal players\n";
    std::uint8_t i{0};
    for (auto &uint : games){
        std::cout << (int) uint << "\t\t\t\t";
        if (i == 2) {
            std::cout << std::endl;
            i = 0;
        } else {
            i++;
        }
    }
    std::cout << std::endl;
}

void GUI::LobbyAssistant::joinGame(){
    this->getGames();
    std::uint8_t gameToJoin;
    std::cout<< "Choose lobby." << std::endl;
    std::cin >> gameToJoin;
    gameToJoin -= 48;
    this->command = COMMAND_JOIN_GAME;
    this->protocol << this->command;
    std::cout<<"mando sala "<< (int) gameToJoin<<std::endl;
    this->protocol << gameToJoin;
    this->waitGameStart();
}

ClientSocket GUI::LobbyAssistant::getSocket() {
    return std::move(this->protocol.getSocket());
}

void GUI::LobbyAssistant::waitGameStart() {
    while (this->playersQuantity < 2){
        this->protocol >> this->playersQuantity;
        std::cout<< "players quantity " << (int) this->playersQuantity<<std::endl;
    }std::cout<<"Empieza\n";
}


