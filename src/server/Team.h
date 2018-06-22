//
// Created by rodrigo on 3/06/18.
//

#ifndef INC_4_WORMS_TEAM_H
#define INC_4_WORMS_TEAM_H

#include <stdint.h>
#include <vector>
#include "Player.h"

namespace Worms {
class Team {
   public:
    Team(std::vector<uint8_t> &playerIDs);
    ~Team(){};
    void checkAlive(std::vector<Player> &players);
    bool isAlive();
    uint8_t getCurrentPlayerID();
    void setCurrentPlayer(uint8_t currentPlayer);
    void endTurn(std::vector<Worms::Player> &players);
    std::uint32_t calculateTotalHealth(std::vector<Worms::Player> &players);

   private:
    std::vector<uint8_t> playerIDs;
    uint8_t currentPlayer{0};
    bool alive{true};
};
}  // namespace Worms

#endif  // INC_4_WORMS_TEAM_H
