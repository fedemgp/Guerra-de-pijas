//
// Created by rodrigo on 20/06/18.
//

#include <fstream>
#include <iostream>

#include "CommunicationProtocol.h"
#include "GameStateMsg.h"
#include "Stream.h"

IO::CommunicationProtocol::CommunicationProtocol(ClientSocket &socket, IO::Stream<IO::ClientGUIMsg> *clientStream,
                                                 IO::Stream<IO::ServerResponse> *output)
        :
        protocol(socket),
        clientStream(clientStream),
        output(output) {
}

void IO::CommunicationProtocol::run() {
    try {
        while (!this->quit) {
            IO::ClientGUIMsg msg;
            if (clientStream->pop(msg)) {
                this->handleClientInput(msg);
            }
        }
    } catch (std::exception &e){
        if (!this->quit){
            std::cerr << "In CommunicationProtocol::run()" << std::endl;
            std::cerr << e.what() << std::endl;
        }
    } catch (...){
        std::cerr << "Unknown Error in CommunicationProtocol::run()" << std::endl;
    }
}

void IO::CommunicationProtocol::startCreateGame(){
    this->command = COMMAND_GET_LEVELS;
    this->protocol << this->command;
    this->protocol >> this->levelsInfo;
    *this->output << IO::ServerResponse{IO::ServerResponseAction::levelsInfo};
}

void IO::CommunicationProtocol::createGame() {
    this->command = COMMAND_CREATE_GAME;
    this->protocol << this->command;
    this->protocol << this->levelToCreate;
    this->getLevelFiles();
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
    this->command = COMMAND_JOIN_GAME;
    this->protocol << this->command;
    this->protocol << this->gameToJoin;
    this->protocol << this->levelOfGameToJoin;
    this->getLevelFiles();
    this->waitGameStart(this->gamesInfo[this->gameToJoin].numTotalPlayers);
}

ClientSocket IO::CommunicationProtocol::getSocket() {
    return std::move(this->protocol.getSocket());
}

void IO::CommunicationProtocol::waitGameStart(uint8_t playersQuantity) {
    while (this->playersQuantity < playersQuantity) {
        this->protocol >> this->playersQuantity;
        *this->output << IO::ServerResponse{IO::ServerResponseAction::playerConnected};
    }
    IO::ServerResponse sr{};
    sr.action = IO::ServerResponseAction::startGame;
    *this->output << sr;
}

void IO::CommunicationProtocol::stop() {
    this->quit = true;
    this->protocol.stopCommunication();
}

void IO::CommunicationProtocol::handleClientInput(IO::ClientGUIMsg &msg) {
    switch (msg.input) {
        case IO::ClientGUIInput::startCreateGame: {
            this->startCreateGame();
            break;
        }
        case IO::ClientGUIInput::levelSelected: {
            this->createGame();
            break;
        }
        case IO::ClientGUIInput::startJoinGame: {
            this->startJoinGame();
            break;
        }
        case IO::ClientGUIInput::joinGame: {
            this->joinGame();
            break;
        }
        case IO::ClientGUIInput::quit: {
            this->quit = true;
            break;
        }
        default: {
            break;
        }
    }
}

void IO::CommunicationProtocol::getLevelFiles() {
    this->protocol >> this->levelPath;
    std::ofstream levelFile(this->levelPath, std::ofstream::binary);
    this->protocol >> levelFile;

    this->protocol >> this->backgroundPath;
    for (auto &background : this->backgroundPath) {
        std::ofstream backgroundFile(background, std::ofstream::binary);
        this->protocol >> backgroundFile;
    }
}

