//
// Created by rodrigo on 3/06/18.
//

#include "Team.h"
#include "Weapons/AerialAttack.h"
#include "Weapons/Banana.h"
#include "Weapons/BaseballBat.h"
#include "Weapons/Bazooka.h"
#include "Weapons/Cluster.h"
#include "Weapons/Dynamite.h"
#include "Weapons/Grenade.h"
#include "Weapons/Holy.h"
#include "Weapons/Mortar.h"
#include "Weapons/Teleport.h"
#include "Weapons/WeaponNone.h"

Worms::Team::Team(std::vector<uint8_t> &playerIDs, std::vector<Player> &players) : playerIDs(std::move(playerIDs)) {
    for (auto id : this->playerIDs){
        players[id].setTeam(this);
    }
    this->initializeWeapons();
}

void Worms::Team::checkAlive(std::vector<Player> &players) {
    if (this->alive) {
        bool teamAlive = false;
        for (auto teamPlayerID : this->playerIDs) {
            if (players[teamPlayerID].getStateId() != Worm::StateID::Dead) {
                teamAlive = true;
            }
        }
        if (!teamAlive) {
            this->alive = false;
        }
    }
}

bool Worms::Team::isAlive() {
    return this->alive;
}

uint8_t Worms::Team::getCurrentPlayerID() {
    return this->playerIDs[this->currentPlayer];
}

void Worms::Team::setCurrentPlayer(uint8_t currentPlayer) {
    this->currentPlayer = currentPlayer;
}

void Worms::Team::endTurn(std::vector<Worms::Player> &players) {
    do {
        this->currentPlayer = (this->currentPlayer + 1) % this->playerIDs.size();
    } while (players[this->getCurrentPlayerID()].getStateId() == Worm::StateID::Dead);
}

std::uint32_t Worms::Team::calculateTotalHealth(std::vector<Worms::Player> &players) {
    std::uint32_t total{0};
    for (auto playerID : this->playerIDs) {
        for (auto &player : players) {
            if (player.getId() == playerID) {
                total += (std::uint32_t)std::floor(player.health);
            }
        }
    }
    return total;
}

std::shared_ptr<Worms::Weapon> Worms::Team::getWeapon(const Worm::WeaponID &id){
    if (this->ammunitionCounter.at(id) == 0) {
        return this->weaponNone;
    }

    switch (id) {
        case Worm::WeaponID::WBazooka:
            return this->bazooka;
        case Worm::WeaponID::WGrenade:
            return this->grenade;
        case Worm::WeaponID::WCluster:
            return this->cluster;
        case Worm::WeaponID::WMortar:
            return this->mortar;
        case Worm::WeaponID::WBanana:
            return this->banana;
        case Worm::WeaponID::WHoly:
            return this->holy;
        case Worm::WeaponID::WAerial:
            return this->aerialAttack;
        case Worm::WeaponID::WDynamite:
            return this->dynamite;
        case Worm::WeaponID::WBaseballBat:
            return this->baseballBat;
        case Worm::WeaponID::WTeleport:
            return this->teleport;
        default:
            return this->weaponNone;
    }
}

void Worms::Team::initializeWeapons(){
    this->aerialAttack = std::shared_ptr<Worms::Weapon>(new ::Weapon::AerialAttack());
    this->banana = std::shared_ptr<Worms::Weapon>(new ::Weapon::Banana(0.0f));
    this->baseballBat = std::shared_ptr<Worms::Weapon>(new ::Weapon::BaseballBat(0.0f));
    this->bazooka = std::shared_ptr<Worms::Weapon>(new ::Weapon::Bazooka(0.0f));
    this->cluster = std::shared_ptr<Worms::Weapon>(new ::Weapon::Cluster(0.0f));
    this->dynamite = std::shared_ptr<Worms::Weapon>(new ::Weapon::Dynamite());
    this->grenade = std::shared_ptr<Worms::Weapon>(new ::Weapon::Grenade(0.0f));
    this->holy = std::shared_ptr<Worms::Weapon>(new ::Weapon::Holy(0.0f));
    this->mortar = std::shared_ptr<Worms::Weapon>(new ::Weapon::Mortar(0.0f));
    this->teleport = std::shared_ptr<Worms::Weapon>(new ::Weapon::Teleport());
    this->weaponNone = std::shared_ptr<Worms::Weapon>(new ::Weapon::WeaponNone());

    this->ammunitionCounter.emplace(Worm::WAerial, 2);
    this->ammunitionCounter.emplace(Worm::WBanana, 2);
    this->ammunitionCounter.emplace(Worm::WBaseballBat, 2);
    this->ammunitionCounter.emplace(Worm::WBazooka, 2);
    this->ammunitionCounter.emplace(Worm::WCluster, 2);
    this->ammunitionCounter.emplace(Worm::WDynamite, 2);
    this->ammunitionCounter.emplace(Worm::WGrenade, 2);
    this->ammunitionCounter.emplace(Worm::WHoly, 2);
    this->ammunitionCounter.emplace(Worm::WMortar, 2);
    this->ammunitionCounter.emplace(Worm::WTeleport, 2);
    // -1 indicates infinite uses
    this->ammunitionCounter.emplace(Worm::WNone, -1);
}

void Worms::Team::weaponUsed(const Worm::WeaponID weaponID) {
    if (this->ammunitionCounter.at(weaponID) > 0) {
        this->ammunitionCounter.at(weaponID)--;
    }
}
