/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 17/06/18
 */

#include "GamesGetter.h"

void GamesGetter::operator()(const std::list<Worms::Lobby> &lobbies){
    for (auto &lobby : lobbies) {
        IO::GameInfo gameInfo{lobby.getID(),
                              lobby.getActualPlayers(),
                              lobby.getPlayersQuantity()};
        this->gamesInfo.emplace_back(gameInfo);
    }
}
