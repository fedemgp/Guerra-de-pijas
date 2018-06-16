//
// Created by rodrigo on 15/06/18.
//

#ifndef INC_4_WORMS_LOBBIES_H
#define INC_4_WORMS_LOBBIES_H


#include <vector>
#include "Lobby.h"

namespace Worms {
    class Lobbies {
    public:
        Lobbies();

        void createGame(int playerID);
        const std::vector<Lobby> & getGames();
        void joinGame(int gameID, int playerID);

    private:
        std::vector<Lobby> lobbies;
    };
}


#endif //INC_4_WORMS_LOBBIES_H
