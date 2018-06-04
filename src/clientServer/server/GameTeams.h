//
// Created by rodrigo on 3/06/18.
//

#ifndef INC_4_WORMS_TEAMS_H
#define INC_4_WORMS_TEAMS_H

#include <vector>
#include "Player.h"
#include "Team.h"

namespace Worms {
class GameTeams {
   public:
    GameTeams() = default;
    ~GameTeams(){};
    void makeTeams(std::vector<Player> &players, uint8_t numTeams);

    void checkAlive(std::vector<Player> &players);

    void endTurn(std::vector<Player> &players);

    char getCurrentPlayerID();

    uint8_t getCurrentTeam();

   private:
    std::vector<Team> teams;
    uint8_t currentTeam{0};
};
}

#endif  // INC_4_WORMS_TEAMS_H
