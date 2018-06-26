//
// Created by rodrigo on 15/06/18.
//

#ifndef INC_4_WORMS_LOBBIES_H
#define INC_4_WORMS_LOBBIES_H


#include <list>
#include <mutex>

#include "GamesGetter.h"
#include "Lobby.h"
#include "Observer.h"

namespace Worms {
    class Lobbies {
    public:
        explicit Lobbies(const std::vector<IO::LevelData> &levels);
        ~Lobbies();
        void configure();
        void createGame(int playerID, std::vector<Observer *> lobbyObservers, uint8_t levelSelected);
        void getGames(GamesGetter &getter);
        void joinGame(int gameID, int playerID, Observer *lobbyObserver);
        const std::vector<IO::LevelInfo> &getLevels();
        const IO::LevelData & getLevelData(uint8_t levelSelected);
        std::list<Lobby> &getLobbies();

    private:
        std::mutex mutex;
        std::list<Lobby> lobbies;
        uint8_t idLobby{0};
        const std::vector<IO::LevelData> &levels;
        std::vector<IO::LevelInfo> levelsInfo;
    };
}


#endif //INC_4_WORMS_LOBBIES_H
