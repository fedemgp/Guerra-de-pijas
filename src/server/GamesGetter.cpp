/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 17/06/18
 */

#include "GamesGetter.h"

void GamesGetter::operator()(const std::list<Worms::Lobby> &lobbies){
    for (auto &lobby : lobbies) {
        this->lobbies.emplace_back(lobby.getID());
        this->lobbies.emplace_back(lobby.getActualPlayers());
        this->lobbies.emplace_back(lobby.getPlayersQuantity());
    }
}
