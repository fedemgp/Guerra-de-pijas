//
// Created by rodrigo on 15/06/18.
//

#include <fstream>
#include <iostream>

#include "GameLobbyAssistant.h"
#include <GameStateMsg.h>
#include "Protocol.h"
#include "Lobbies.h"
#include "GamesGetter.h"

Worms::GameLobbyAssistant::GameLobbyAssistant(CommunicationSocket &&communicationSocket, Lobbies &lobbies, int id,
                                              Observer *lobbyObs) :
        protocol(communicationSocket),
        lobbies(lobbies),
        playerID(id) {
    this->lobbyObservers.emplace_back(lobbyObs);
    this->lobbyObservers.emplace_back(this);
}

void Worms::GameLobbyAssistant::run() {
    try {
        std::uint8_t command{COMMAND_GET_LEVELS};
        while (!this->quit) {
            this->protocol >> command;
            std::cout << "command: " << (int) command << std::endl;
            switch (command) {
                case COMMAND_GET_LEVELS:
                    this->getLevels();
                    break;
                case COMMAND_CREATE_GAME:
                    this->createGame();
                    break;
                case COMMAND_GET_GAMES:
                    this->getGames();
                    break;
                case COMMAND_JOIN_GAME:
                    this->joinGame();
                    break;
            }
        }
//        this->createGame();
//        this->createGame();
//        this->createGame();
//        this->getGames();
    } catch (std::exception &e) {
        std::cerr << "In GameLobbyAssistant::run()" << std::endl;
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unkown error in GameLobbyAssistant::run()" << std::endl;
    }
}

void Worms::GameLobbyAssistant::stop() {
    this->finished = true;
}

void Worms::GameLobbyAssistant::getLevels() {
//    std::vector<IO::LevelInfo> levelsInfo;
//    IO::LevelInfo levelInfo{"First Stage", 2};
//    levelsInfo.emplace_back(levelInfo);
//    levelInfo = {"Second Stage", 3};
//    levelsInfo.emplace_back(levelInfo);
//    levelInfo = {"Third Stage", 4};
//    levelsInfo.emplace_back(levelInfo);


    this->protocol << this->lobbies.getLevels();
}

void Worms::GameLobbyAssistant::createGame() {
    uint8_t levelSelected{0};
    this->protocol >> levelSelected;
    this->sendLevelFiles(levelSelected);

    this->lobbies.createGame(this->playerID, this->lobbyObservers, levelSelected);
    this->quit = true;
}

void Worms::GameLobbyAssistant::getGames() {
    GamesGetter getter;
    this->lobbies.getGames(getter);
    this->protocol << getter.gamesInfo;
}

void Worms::GameLobbyAssistant::joinGame() {
    std::uint8_t gameID{0};
    this->protocol >> gameID;
    std::cout << "Joining game with ID " << (int) gameID << std::endl;
    this->sendLevelFiles(gameID);
    this->lobbies.joinGame(gameID, this->playerID, this);
    this->quit = true;
}

void Worms::GameLobbyAssistant::onNotify(Subject &subject, Event event) {
    switch (event) {
        case Event::NewPlayer: {
            auto &lobby = dynamic_cast<Lobby &>(subject);
            std::cout<<"new Player, actualPlayers: "<< (int) lobby.getActualPlayers()<<std::endl;
            this->protocol << lobby.getActualPlayers();
            break;
        }
        default: {
            break;
        }
    }
}

CommunicationSocket Worms::GameLobbyAssistant::getSocket() {
    return std::move(this->protocol.getSocket());
}

int Worms::GameLobbyAssistant::getPlayerID() const{
    return this->playerID;
}

bool Worms::GameLobbyAssistant::itsOver() const{
    return this->finished;
}

void Worms::GameLobbyAssistant::sendLevelFiles(uint8_t level) {
    const IO::LevelData &levelData = this->lobbies.getLevelData(level);
    this->protocol << levelData.levelName;
//    std::string levelFilename(levelData.levelPath);
    std::ifstream levelFile(levelData.levelPath, std::ifstream::binary);
    this->protocol << levelFile;

    this->protocol << levelData.backgroundName;
    for (auto &background : levelData.backgroundPath) {
//        std::string backgroundFilename(background);
        std::ifstream backgroundFile(background, std::ifstream::binary);
        this->protocol << backgroundFile;
    }
}
