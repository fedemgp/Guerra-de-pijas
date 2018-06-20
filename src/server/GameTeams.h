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

    bool endTurn(std::vector<Player> &players);

    char getCurrentPlayerID();

    uint8_t getCurrentTeam();

    std::uint8_t getWinner();

   private:
    std::vector<Team> teams;
    std::uint8_t deadTeams{0};
    uint8_t currentTeam{0};
};
}

#endif  // INC_4_WORMS_TEAMS_H
