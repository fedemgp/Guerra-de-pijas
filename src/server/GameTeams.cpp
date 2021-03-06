//
// Created by rodrigo on 3/06/18.
//

#include "GameTeams.h"
#include <random>

void Worms::GameTeams::makeTeams(std::vector<Worms::Player> &players, uint8_t numTeams,
                                 const std::map<Worm::WeaponID, std::int16_t> &ammoCounter) {
    uint8_t numPlayers = players.size();

    this->teams.reserve(numTeams);
    std::vector<uint8_t> playersNum(numPlayers);
    for (uint8_t i = 0; i < numPlayers; i++) {
        playersNum[i] = i;
    }

    std::random_device rnd_device;
    std::mt19937 mersenne_engine(rnd_device());

    shuffle(playersNum.begin(), playersNum.end(), mersenne_engine);

    uint8_t maxTeamPlayers =
        (numPlayers % numTeams == 0) ? numPlayers / numTeams : numPlayers / numTeams + 1;
    std::vector<uint8_t> numPlayersPerTeam(numTeams);
    for (uint8_t i = 0, nP = numPlayers, nT = numTeams; i < numPlayersPerTeam.size(); i++) {
        numPlayersPerTeam[i] = nP / nT;
        nP -= numPlayersPerTeam[i];
        nT--;
    }
    std::vector<uint8_t> playerIDs;
    for (uint8_t i = 0, currentTeam = 0; i < numPlayers; i++) {
        //        this->teams[currentTeam].players.emplace_back(players[playersNum[i]].getId());
        playerIDs.emplace_back(players[playersNum[i]].getId());
        players[playersNum[i]].setTeamID(currentTeam);
        if (numPlayersPerTeam[currentTeam] < maxTeamPlayers) {
            players[playersNum[i]].increaseHealth(25.0f);
        }
        if (playerIDs.size() == numPlayersPerTeam[currentTeam]) {
            this->teams.emplace_back(playerIDs, players, ammoCounter);
            playerIDs.clear();
            currentTeam++;
        }
    }
}

void Worms::GameTeams::checkAlive(std::vector<Worms::Player> &players) {
    std::uint8_t teamID{0};
    for (auto &team : this->teams) {
        team.checkAlive(players);
        if (!team.isAlive() && std::find(this->deadTeams.begin(), this->deadTeams.end(), teamID) == this->deadTeams.end()) {
            this->deadTeams.emplace_back(teamID);
        }
        teamID++;
    }
}

bool Worms::GameTeams::endTurn(std::vector<Player> &players) {
    this->checkAlive(players);

    do {
        this->currentTeam = (this->currentTeam + 1) % this->teams.size();
    } while (!this->teams[this->currentTeam].isAlive());

    this->teams[this->currentTeam].endTurn(players);

    if (this->deadTeams.size() >= this->teams.size() - 1) {
        return true;
    } else {
        return false;
    }
}

std::vector<std::uint32_t> Worms::GameTeams::getTotalHealth(std::vector<Worms::Player> &players) {
    uint8_t i{0};
    std::vector<std::uint32_t> teamHealths;
    for (auto &team : this->teams) {
        teamHealths.emplace_back(team.calculateTotalHealth(players));
        i++;
    }
    return std::move(teamHealths);
}

uint8_t Worms::GameTeams::getCurrentPlayerID() {
    return this->teams[this->currentTeam].getCurrentPlayerID();
}

uint8_t Worms::GameTeams::getCurrentTeamID() {
    return this->currentTeam;
}

uint8_t Worms::GameTeams::getWinner() {
    std::uint8_t winner{0};
    for (auto &team : this->teams) {
        if (team.isAlive()) {
            return winner;
        }
        winner++;
    }
    return winner;
}

std::uint8_t Worms::GameTeams::getTeamQuantity() const {
    return (std::uint8_t) this->teams.size();
}

Worms::Team &Worms::GameTeams::getCurrentTeam() {
    return this->teams[this->currentTeam];
}

void Worms::GameTeams::weaponUsed(const Worm::WeaponID weaponID) {
    this->teams[this->currentTeam].weaponUsed(weaponID);
}

void Worms::GameTeams::serialize(IO::GameStateMsg &msg) const {
    this->teams[this->currentTeam].serialize(msg);
}

void Worms::GameTeams::kill(uint8_t team, std::vector<Worms::Player> &players) {
    this->teams[team].kill(players);
}
