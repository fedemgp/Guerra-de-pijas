/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#ifndef __GAME_STATE_MSG_H__
#define __GAME_STATE_MSG_H__

#define WORMS_QUANTITY 20
#define BULLETS_QUANTITY 7
#define TOTAL_TEAM_QUANTITY 5
#define WEAPONS_QUANTITY 10

#define POWER_CHARGE_TIME 5.0f

#define ELAPSED_TURN "elapT"
#define WIND_INTENSITY "windI"
#define CURRENT_WORM "curW"
#define CURRENT_WORM_TO_FOLLOW "curWF"
#define CURRENT_TEAM "curT"
#define NUM_WORMS "numW"
#define NUM_TEAMS_KEY "numT"
#define WORMS_TEAM "wTeam"
#define WORM_DIRECTION "wDir"
#define WORM_HEALTH_KEY "wHealth"
#define TEAM_HEALTHS "tHealth"
#define WORM_POSITION "wPos"
#define WORM_STATES "states"
#define CURRENT_WEAPON "curWeap"
#define WORM_ANGLES "wAngle"
#define BULLET_QUANTITY_KEY "bullQ"
#define BULLET_POSITION "bullP"
#define BULLET_ANGLES "bullA"
#define WEAPON_AMMUNITION "wAmmo"
#define BULLET_TYPES "bullT"
#define PROCESSING_INPUTS "procIn"
#define CURRENT_TURN_TIME "curTime"
#define GAME_ENDED "gameEnd"
#define WINNER "win"
#define USED_TOOL "toolUsed"
#define WAITING_FOR_NEXT_TURN "waiting"

#include <netinet/in.h>
#include <stdint.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstdint>
#include <stdint-gcc.h>

#include "Direction.h"
#include "Exception.h"
#include "Point.h"

namespace Worm {
enum class StateID {
    Walk,
    Still,
    StartJump,
    Jumping,
    EndJump,
    StartBackFlip,
    BackFlipping,
    EndBackFlip,
    Hit,
    Die,
    Dead,
    Drowning,
    Falling,
    Land,
    Sliding,
    Teleporting,
    Teleported,
    Batting
};
enum WeaponID {
    WNone,
    WBazooka,
    WGrenade,
    WCluster,
    WMortar,
    WBanana,
    WHoly,
    WExplode,
    WFragment,
    WAerial,
    WDynamite,
    WTeleport,
    WBaseballBat
};
}  // namespace Worm

namespace IO {
    enum class ClientGUIInput {
        startCreateGame,
        startJoinGame,
        quit,
        levelSelected,
        joinGame
    };
    enum class ServerResponseAction {
        startGame,
        levelsInfo,
        playerConnected,
        gamesInfo,
    };

    struct ClientGUIMsg {
        ClientGUIMsg() = default;
        explicit ClientGUIMsg(ClientGUIInput input) :
                input(input) {};
        ClientGUIInput input;
    };
    struct ServerResponse {
        ServerResponseAction action;
    };

    //TODO put this in dedicated file.
    enum class ServerInternalAction {
        lobbyFinished,
        quit
    };

    struct ServerInternalMsg {
        ServerInternalAction action;
    };

    struct LevelInfo {
        uint8_t id;
        std::string name;
        uint8_t playersQuantity;
    };

    struct GameInfo {
        uint8_t gameID;
        uint8_t levelID;
        std::string levelName;
        uint8_t numCurrentPlayers;
        uint8_t numTotalPlayers;
    };

    struct LevelData {
        std::string levelPath;
        std::string levelName;
        std::vector<std::string> backgroundPath;
        std::vector<std::string> backgroundName;
    };

    struct LevelsInfo : public ServerResponse {
        LevelsInfo(ServerResponseAction action, std::vector<LevelInfo> &levelsInfo) :
                action(action),
                levelsInfo(std::move(levelsInfo)) {}
        ServerResponseAction action;
        std::vector<LevelInfo> levelsInfo;
    };
    struct LevelSelected : public ClientGUIMsg {
        LevelSelected(ClientGUIInput input, unsigned int levelSelected) :
                ClientGUIMsg(input),
                levelSelected(levelSelected) {};
        unsigned int levelSelected;
    };
enum class PlayerInput {
    moveNone,
    moveRight,
    moveLeft,
    startJump,
    stopMove,
    startBackFlip,
    bazooka,
    pointUp,
    pointDown,
    startShot,
    endShot,
    grenade,
    cluster,
    mortar,
    banana,
    holy,
    timeout1,
    timeout2,
    timeout3,
    timeout4,
    timeout5,
    positionSelected,
    aerialAttack,
    dynamite,
    teleport,
    baseballBat
};

struct PlayerMsg {
    PlayerInput input;
    Math::Point<float> position{0.0f, 0.0f};

    std::vector<std::uint8_t> serialize() {
        std::vector<std::uint8_t> buffer;

        buffer.emplace_back(static_cast<std::uint8_t>(this->input));
        std::uint32_t netX = htonl(*((std::uint32_t *) &this->position.x));
        std::uint32_t netY = htonl(*((std::uint32_t *) &this->position.y));
        for (int i = 0; i < 4; i++){
            buffer.emplace_back(((std::uint8_t *) &netX)[i]);
        }

        for (int i = 0; i < 4; i++){
            buffer.emplace_back(((std::uint8_t *) &netY)[i]);
        }
        return std::move(buffer);
    }

    void deserialize(std::vector<std::uint8_t> &buffer) {
        this->input = static_cast<PlayerInput>(buffer[0]);

        std::uint32_t netX = *((std::uint32_t *)(buffer.data() + 1)),
                netY = *((std::uint32_t *)(buffer.data() + 5));
        netX = ntohl(netX);
        netY = ntohl(netY);

        this->position.x = *(float *) (&netX);
        this->position.y = *(float *) (&netY);
    }
};

struct GameStateMsg {
    std::uint16_t elapsedTurnSeconds;
    std::int8_t windIntensity;
    std::uint8_t currentWorm;
    std::uint8_t currentWormToFollow;
    std::uint8_t currentTeam;
    std::uint8_t num_worms;
    std::uint8_t num_teams;
    std::uint8_t wormsTeam[WORMS_QUANTITY];
    Worm::Direction wormsDirection[WORMS_QUANTITY];
    std::uint16_t wormsHealth[WORMS_QUANTITY];
    std::uint32_t teamHealths[TOTAL_TEAM_QUANTITY];
    float positions[WORMS_QUANTITY * 2];
    Worm::StateID stateIDs[WORMS_QUANTITY];
    Worm::WeaponID activePlayerWeapon;
    float activePlayerAngle;
    uint8_t bulletsQuantity;
    float bullets[2 * BULLETS_QUANTITY];
    float bulletsAngle[BULLETS_QUANTITY];
    Worm::WeaponID bulletType[BULLETS_QUANTITY];
    std::int16_t weaponAmmunition[WEAPONS_QUANTITY];

    bool processingInputs;
    std::uint16_t currentPlayerTurnTime;
    bool gameEnded;
    std::uint8_t winner;
    bool playerUsedTool;
    bool waitingForNextTurn;

    std::vector<std::uint8_t> serialize() {
        std::vector<std::uint8_t> buffer;

//        buffer.emplace_back(static_cast<std::uint8_t>(this->input));
//        std::uint32_t netX = htonl(*((std::uint32_t *) &this->position.x));
//        std::uint32_t netY = htonl(*((std::uint32_t *) &this->position.y));
//
//        for (int i = 0; i < 4; i++){
//            buffer.emplace_back(((std::uint8_t *) &netX)[i]);
//        }
        std::uint16_t ishort = htons(this->elapsedTurnSeconds);
        for (int i = 0; i < 2; i++){
            buffer.emplace_back(((std::uint8_t *) &ishort)[i]);
        }

        buffer.emplace_back(this->windIntensity);
        buffer.emplace_back(this->currentWorm);
        buffer.emplace_back(this->currentWormToFollow);
        buffer.emplace_back(this->currentTeam);
        buffer.emplace_back(this->num_worms);
        buffer.emplace_back(this->num_teams);

        for(int i = 0 ; i < WORMS_QUANTITY; i++){
            buffer.emplace_back(this->wormsTeam[i]);
        }

        for(int i = 0 ; i < WORMS_QUANTITY; i++){
            buffer.emplace_back(static_cast<std::uint8_t >(this->wormsDirection[i]));
        }

        for(int i = 0; i < WORMS_QUANTITY; i++){
            ishort = htons(this->wormsHealth[i]);
            for (int j = 0; j < 2; j++){
                buffer.emplace_back(((std::uint8_t *) &ishort)[j]);
            }
        }

        std::uint32_t ilong{0};
        for(int i= 0; i < TOTAL_TEAM_QUANTITY ; i++){
            ilong = htonl(this->teamHealths[i]);
            for (int j = 0; j < 4; j++){
                buffer.emplace_back(((std::uint8_t *) &ilong)[j]);
            }
        }
        int posQuantity = 2 * WORMS_QUANTITY;
        for(int i = 0; i < posQuantity; i++){
            ilong = htonl(*((std::uint32_t *) &this->positions[i]));
            for (int j = 0; j < 4; j++){
                buffer.emplace_back(((std::uint8_t *) &ilong)[j]);
            }
        }

        for(int i = 0; i < WORMS_QUANTITY; i++){
            buffer.emplace_back((std::uint8_t) stateIDs[i]);
        }

        buffer.emplace_back((std::uint8_t) activePlayerWeapon);

        ilong = htonl(*((std::uint32_t *) &this->activePlayerAngle));
        for (int j = 0; j < 4; j++){
            buffer.emplace_back(((std::uint8_t *) &ilong)[j]);
        }

        buffer.emplace_back(this->bulletsQuantity);

        int bullPosQ = 2 * BULLETS_QUANTITY;
        for(int i = 0; i < bullPosQ; i++){
            ilong = htonl(*((std::uint32_t *) &this->bullets[i]));
            for (int j = 0; j < 4; j++){
                buffer.emplace_back(((std::uint8_t *) &ilong)[j]);
            }
        }

        for(int i = 0; i < BULLETS_QUANTITY; i++){
            ilong = htonl(*((std::uint32_t *) &this->bulletsAngle[i]));
            for (int j = 0; j < 4; j++){
                buffer.emplace_back(((std::uint8_t *) &ilong)[j]);
            }
        }

        for(int i = 0; i < BULLETS_QUANTITY; i++){
            buffer.emplace_back((std::uint8_t) this->bulletType[i]);
        }

        for(int i = 0; i < WEAPONS_QUANTITY; i++){
            ishort = htons((std::uint16_t) this->weaponAmmunition[i]);
            for (int j = 0; j < 2; j++){
                buffer.emplace_back(((std::uint8_t *) &ishort)[j]);
            }
        }

        buffer.emplace_back((std::uint8_t) this->processingInputs);

        ishort = htons(this->currentPlayerTurnTime);
        for (int j = 0; j < 2; j++){
            buffer.emplace_back(((std::uint8_t *) &ishort)[j]);
        }

        buffer.emplace_back((std::uint8_t) this->gameEnded);
        buffer.emplace_back(this->winner);
        buffer.emplace_back((std::uint8_t) this->playerUsedTool);
        buffer.emplace_back((std::uint8_t) this->waitingForNextTurn);

        return std::move(buffer);
    }

    void deserialize(std::vector<std::uint8_t> &buffer) {
        std::size_t i{0};

        std::uint16_t ishort = *((std::uint16_t *)(buffer.data()));
        this->elapsedTurnSeconds = ntohs(ishort);
        i+=2;
        this->windIntensity = (std::int8_t) buffer[i++];
        this->currentWorm = buffer[i++];
        this->currentWormToFollow = buffer[i++];
        this->currentTeam = buffer[i++];
        this->num_worms = buffer[i++];
        this->num_teams = buffer[i++];

        for(int j = 0; j < WORMS_QUANTITY; j++){
            this->wormsTeam[j] = buffer[i++];
        }

        for(int j = 0; j < WORMS_QUANTITY; j++){
            this->wormsDirection[j] = (Worm::Direction) buffer[i++];
        }

        for (int j = 0; j < WORMS_QUANTITY; j++){
            ishort = *((std::uint16_t *)(buffer.data() + i));
            this->wormsHealth[j] = ntohs(ishort);
            i += 2;
        }

        std::uint32_t ilong{0};
        for (int j = 0; j < TOTAL_TEAM_QUANTITY; j++){
            ilong = *((std::uint32_t *)(buffer.data() + i));
            this->teamHealths[j] = ntohl(ilong);
            i += 4;
        }

        int posQ = 2 * WORMS_QUANTITY;
        for (int j = 0; j < posQ; j++){
            ilong = *((std::uint32_t *)(buffer.data() + i));
            ilong = ntohl(ilong);
            this->positions[j] = *(float *) (&ilong);
            i += 4;
        }

        for (int j = 0; j < WORMS_QUANTITY ; j++){
            this->stateIDs[j] = static_cast<Worm::StateID>(buffer[i++]);
        }

        this->activePlayerWeapon = static_cast<Worm::WeaponID>(buffer[i++]);

        ilong = *((std::uint32_t *)(buffer.data() + i));
        ilong = ntohl(ilong);
        this->activePlayerAngle = *(float *) (&ilong);
        i += 4;

        this->bulletsQuantity = buffer[i++];

        int bullPosQ = BULLETS_QUANTITY * 2;
        for (int j = 0; j < bullPosQ; j++){
            ilong = *((std::uint32_t *)(buffer.data() + i));
            ilong = ntohl(ilong);
            this->bullets[j] = *(float *) (&ilong);
            i += 4;
        }

        for (int j = 0; j < BULLETS_QUANTITY; j++){
            ilong = *((std::uint32_t *)(buffer.data() + i));
            ilong = ntohl(ilong);
            this->bulletsAngle[j] = *(float *) (&ilong);
            i += 4;
        }

        for (int j = 0; j < BULLETS_QUANTITY; j++){
            this->bulletType[j] = static_cast<Worm::WeaponID>(buffer[i++]);
        }

        for (int j = 0; j < BULLETS_QUANTITY; j++){
            ishort = *((std::uint16_t *)(buffer.data() + i));
            this->weaponAmmunition[j] = ntohs(ishort);
            i += 2;
        }

        this->processingInputs = (bool) buffer[i++];

        ishort = *((std::uint16_t *)(buffer.data() + i));
        this->currentPlayerTurnTime = ntohs(ishort);
        i += 2;

        this->gameEnded = (bool) buffer[i++];
        this->winner = buffer[i++];
        this->playerUsedTool = (bool) buffer[i++];
        this->waitingForNextTurn = (bool) buffer[i++];

    }
};
}  // namespace IO

#endif  //__GAME_STATE_MSG_H__
