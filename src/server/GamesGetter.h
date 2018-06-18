/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 17/06/18
 */

#ifndef __GamesGetter_H__
#define __GamesGetter_H__

#include <string>

#include "Lobby.h"

struct GamesGetter{
public:
    void operator()(const std::vector<Worms::Lobby> &lobbies);
    std::vector<uint8_t> lobbies;
};


#endif //__GamesGetter_H__
