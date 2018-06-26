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
    void makeTeams(std::vector<Player> &players, uint8_t numTeams, const std::map<Worm::WeaponID, std::int16_t> &ammoCounter);
    void checkAlive(std::vector<Player> &players);
    bool endTurn(std::vector<Player> &players);
    uint8_t getCurrentPlayerID();
    std::uint8_t getTeamQuantity() const;
    uint8_t getCurrentTeamID();
    Team &getCurrentTeam();
    std::uint8_t getWinner();
    std::vector<std::uint32_t> getTotalHealth(std::vector<Worms::Player> &players);
    void weaponUsed(const Worm::WeaponID weaponID);
    void serialize(IO::GameStateMsg &msg) const;

    void kill(uint8_t team, std::vector<Player> &players);

private:
    std::vector<Team> teams;
    std::uint8_t deadTeams{0};
    uint8_t currentTeam{0};
};
}

#endif  // INC_4_WORMS_TEAMS_H
