/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 17/06/18
 */

#ifndef __GamesGetter_H__
#define __GamesGetter_H__

#include <list>
#include <string>

#include "GameStateMsg.h"
#include "Lobby.h"

struct GamesGetter{
public:
    void operator()(const std::list<Worms::Lobby> &lobbies);
    std::vector<IO::GameInfo> gamesInfo;
};


#endif //__GamesGetter_H__
