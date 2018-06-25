//
// Created by rodrigo on 20/06/18.
//

#include <iostream>
#include <GameStateMsg.h>
#include <Stream.h>
#include "CommunicationProtocol.h"

IO::CommunicationProtocol::CommunicationProtocol(ClientSocket &socket, IO::Stream<IO::ClientGUIMsg> *clientStream,
                                                 IO::Stream<IO::ServerResponse> *output)
        :
        protocol(socket),
        clientStream(clientStream),
        output(output) {
}

void IO::CommunicationProtocol::run() {
    while (!this->quit) {
        IO::ClientGUIMsg msg;
        if (clientStream->pop(msg)) {
            this->handleClientInput(msg);
        }
    }
    std::cout<<"dhsdfhs";
}

//void IO::CommunicationProtocol::clearScreen(){
//    std::cout << std::string(100, '\n');
//}

//void IO::CommunicationProtocol::printCommands() {
//    std::cout << "Select option" << std::endl;
//    std::cout << COMMAND_CREATE_GAME << " Create game." << std::endl
//              << COMMAND_JOIN_GAME << " Shows current lobbies. Must select one." << std::endl;
//}

//TODO notify to the main thread that player select this so it can render properly
void IO::CommunicationProtocol::startCreateGame(){
    this->command = COMMAND_GET_LEVELS;
    this->protocol << this->command;
//    std::vector<IO::LevelInfo> levelsInfo;
//    this->protocol >> levelsInfo;
    this->protocol >> this->levelsInfo;
//    *this->output << IO::LevelsInfo{IO::ServerResponseAction::levelsInfo, levelsInfo};
    *this->output << IO::ServerResponse{IO::ServerResponseAction::levelsInfo};
}

void IO::CommunicationProtocol::createGame() {
    this->command = COMMAND_CREATE_GAME;
    this->protocol << this->command;
    this->protocol << this->levelToCreate;
    this->waitGameStart(this->levelsInfo[this->levelToCreate].playersQuantity);
}

void IO::CommunicationProtocol::startJoinGame(){
    this->command = COMMAND_GET_GAMES;
    this->protocol << this->command;
    this->protocol >> this->gamesInfo;
    
    IO::ServerResponse sr;
    sr.action = IO::ServerResponseAction::gamesInfo;
    *this->output << sr;
}

void IO::CommunicationProtocol::joinGame() {
    

//    std::uint8_t gameToJoin;
//    std::cout<< "Choose lobby." << std::endl;
//    std::cin >> gameToJoin;
//    gameToJoin -= 48;
    this->command = COMMAND_JOIN_GAME;
    this->protocol << this->command;
    std::cout<<"mando sala "<< (int) this->gameToJoin <<std::endl;
    this->protocol << this->gameToJoin;
    this->waitGameStart(this->gamesInfo[this->gameToJoin].numTotalPlayers);
}

ClientSocket IO::CommunicationProtocol::getSocket() {
    return std::move(this->protocol.getSocket());
}

void IO::CommunicationProtocol::waitGameStart(uint8_t playersQuantity) {
    while (this->playersQuantity < playersQuantity) {
        this->protocol >> this->playersQuantity;
        *this->output << IO::ServerResponse{IO::ServerResponseAction::playerConnected};
        std::cout<< "players quantity " << (int) this->playersQuantity<<std::endl;
    } std::cout<<"Empieza\n";
    IO::ServerResponse sr{};
    sr.action = IO::ServerResponseAction::startGame;
    *this->output << sr;
}

void IO::CommunicationProtocol::stop() {
    this->quit = true;
}

void IO::CommunicationProtocol::handleClientInput(IO::ClientGUIMsg &msg) {
    switch (msg.input) {
        case IO::ClientGUIInput::startCreateGame: {
            std::cout << " asdasd";
            this->startCreateGame();
            break;
        }
        case IO::ClientGUIInput::levelSelected: {
            std::cout << " asdasd";
            this->createGame();
            break;
        }
        case IO::ClientGUIInput::startJoinGame: {
            std::cout << " asdasd";
            this->startJoinGame();
            break;
        }
        case IO::ClientGUIInput::joinGame: {
            std::cout << " asdasd";
            this->joinGame();
            break;
        }
        case IO::ClientGUIInput::quit: {
            std::cout << " asdasd";
            this->quit = true;
            break;
        }
        default: {
            break;
        }
    }
}

