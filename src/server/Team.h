//
// Created by rodrigo on 3/06/18.
//

#ifndef INC_4_WORMS_TEAM_H
#define INC_4_WORMS_TEAM_H

#include <cstdint>
#include <stdint.h>
#include <vector>
#include "Weapons/Weapon.h"

namespace Worms {
    class Player;
class Team {
   public:
    Team(std::vector<uint8_t> &playerIDs, std::vector<Player> &players);
    ~Team() = default;
    void checkAlive(std::vector<Player> &players);
    bool isAlive();
    uint8_t getCurrentPlayerID();
    void setCurrentPlayer(uint8_t currentPlayer);
    void endTurn(std::vector<Worms::Player> &players);
    std::uint32_t calculateTotalHealth(std::vector<Worms::Player> &players);

    std::shared_ptr<Weapon> getWeapon(const Worm::WeaponID &id);

private:
    std::vector<uint8_t> playerIDs;
    uint8_t currentPlayer{0};
    bool alive{true};
    std::shared_ptr<Weapon> aerialAttack{nullptr};
    std::shared_ptr<Weapon> banana{nullptr};
    std::shared_ptr<Weapon> baseballBat{nullptr};
    std::shared_ptr<Weapon> bazooka{nullptr};
    std::shared_ptr<Weapon> cluster{nullptr};
    std::shared_ptr<Weapon> dynamite{nullptr};
    std::shared_ptr<Weapon> grenade{nullptr};
    std::shared_ptr<Weapon> holy{nullptr};
    std::shared_ptr<Weapon> mortar{nullptr};
    std::shared_ptr<Weapon> teleport{nullptr};

    void initializeWeapons();
};
}  // namespace Worms

#endif  // INC_4_WORMS_TEAM_H
