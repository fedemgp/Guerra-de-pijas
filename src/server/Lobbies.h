//
// Created by rodrigo on 15/06/18.
//

#ifndef INC_4_WORMS_LOBBIES_H
#define INC_4_WORMS_LOBBIES_H


#include <mutex>
#include <vector>

#include "GamesGetter.h"
#include "Lobby.h"

namespace Worms {
    class Lobbies {
    public:
        Lobbies() = default;

        void createGame(int playerID);
        void getGames(GamesGetter &getter);
        void joinGame(int gameID, int playerID);

    private:
        std::mutex mutex;
        std::vector<Lobby> lobbies;
        uint8_t idLobby{0};
    };
}


#endif //INC_4_WORMS_LOBBIES_H
