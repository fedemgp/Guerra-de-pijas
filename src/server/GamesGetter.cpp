/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 17/06/18
 */

#include <sstream>

#include "GamesGetter.h"

void GamesGetter::operator()(const std::vector<Worms::Lobby> &lobbies){
    this->lobbies.emplace_back("Room ID\t\tPlayers in room\t\tTotal players\n");
    for (auto lobby : lobbies){
        std::ostringstream oss;
        oss << (int) lobby.getID() << "\t\t\t" << (int) lobby.getActualPlayers();
        oss << "\t\t\t\t\t" << (int) lobby.getPlayersQuantity() << std::endl;
        this->lobbies.emplace_back(oss.str());
    }
}
