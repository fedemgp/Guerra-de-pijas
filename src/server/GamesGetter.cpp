/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 17/06/18
 */

#include "GamesGetter.h"

void GamesGetter::operator()(const std::list<Worms::Lobby> &lobbies){
    for (auto &lobby : lobbies) {
        auto &levelInfo = lobby.getLevelInfo();
        IO::GameInfo gameInfo{lobby.getID(),
                              levelInfo.id,
                              levelInfo.name,
                              lobby.getActualPlayers(),
                              levelInfo.playersQuantity};
        this->gamesInfo.emplace_back(gameInfo);
    }
}
