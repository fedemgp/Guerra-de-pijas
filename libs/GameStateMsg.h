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

#define COMMAND_GET_LEVELS 0
#define COMMAND_JOIN_GAME 1
#define COMMAND_GET_GAMES 2
#define COMMAND_CREATE_GAME 3
#define COMMAND_QUIT 5

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

#include "Buffer.h"
#include <netinet/in.h>
#include <stdint.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/yaml.h>
#include <cstring>
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
        serverClosed
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
    baseballBat,
    disconnected
};

struct PlayerMsg {
    PlayerInput input;
    Math::Point<float> position{0.0f, 0.0f};

    std::string serialize() {
        IO::Buffer buffer;

        buffer.append(static_cast<uint8_t>(this->input));
        buffer.appendFloat(this->position.x);
        buffer.appendFloat(this->position.y);

        return buffer.asString();
    }

    void deserialize(const std::string &data) {
        IO::Buffer buffer{data};

        this->input = static_cast<PlayerInput>(buffer.extract<uint8_t>());
        this->position.x = buffer.extractFloat();
        this->position.y = buffer.extractFloat();
    }
//    std::size_t getSerializedSize() {
//        std::size_t length(0);
//        length += sizeof(input);
//        length += sizeof(position.x);
//        length += sizeof(position.y);
//
//        return length;
//    }
//
//    void serialize(void *buffer, std::size_t buffer_size) {
//        if (this->getSerializedSize() > buffer_size) {
//            throw Exception{"PlayerMsg: buffer too small"};
//        }
//
//        /* TODO: serialize each field with hton functions */
//        memcpy(buffer, this, this->getSerializedSize());
//    }
//
//    void deserialize(const void *buffer, std::size_t buffer_size) {
//        if (this->getSerializedSize() != buffer_size) {
//            throw Exception{"PlayerMsg: buffer size mismatch"};
//        }
//
//        /* TODO: deserialize each field with ntoh functions */
//        memcpy(this, buffer, this->getSerializedSize());
//    }
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

    std::string serialize() {
        IO::Buffer buffer;

        buffer.append(this->elapsedTurnSeconds);
        buffer.append(windIntensity);
        buffer.append(currentWorm);
        buffer.append(currentWormToFollow);
        buffer.append(currentTeam);
        buffer.append(num_worms);
        buffer.append(num_teams);

        for(std::size_t i = 0; i < this->num_worms; i++) {
            buffer.append(this->wormsTeam[i]);
            buffer.append(static_cast<uint8_t>(this->wormsDirection[i]));
            buffer.append(this->wormsHealth[i]);
            buffer.appendFloat(this->positions[i * 2]);
            buffer.appendFloat(this->positions[i * 2 + 1]);
            buffer.append(static_cast<uint8_t>(this->stateIDs[i]));
        }

        for(std::size_t i = 0; i < this->num_teams; i++) {
            buffer.append(this->teamHealths[i]);
        }

        buffer.append(static_cast<uint8_t>(this->activePlayerWeapon));
        buffer.appendFloat(this->activePlayerAngle);
        buffer.append(this->bulletsQuantity);

        for(std::size_t i = 0; i < this->bulletsQuantity; i++) {
            buffer.appendFloat(this->bullets[i * 2]);
            buffer.appendFloat(this->bullets[i * 2 + 1]);
            buffer.appendFloat(this->bulletsAngle[i]);
            buffer.append(static_cast<uint8_t>(this->bulletType[i]));
        }

        for(std::size_t i = 0; i < WEAPONS_QUANTITY; i++) {
            buffer.append(weaponAmmunition[i]);
        }

        buffer.append(static_cast<uint8_t>(this->processingInputs));
        buffer.append(this->currentPlayerTurnTime);
        buffer.append(static_cast<uint8_t>(this->gameEnded));
        buffer.append(this->winner);
        buffer.append(static_cast<uint8_t>(this->playerUsedTool));
        buffer.append(static_cast<uint8_t>(this->waitingForNextTurn));

        return buffer.asString();
    }

    void deserialize(const std::string &data) {
        IO::Buffer buffer{data};

        this->elapsedTurnSeconds = buffer.extract<uint16_t>();
        this->windIntensity = buffer.extract<uint8_t>();
        this->currentWorm = buffer.extract<uint8_t>();
        this->currentWormToFollow = buffer.extract<uint8_t>();
        this->currentTeam = buffer.extract<uint8_t>();
        this->num_worms = buffer.extract<uint8_t>();
        this->num_teams = buffer.extract<uint8_t>();

        for(std::size_t i = 0; i < this->num_worms; i++) {
            this->wormsTeam[i] = buffer.extract<uint8_t>();
            this->wormsDirection[i] = static_cast<Worm::Direction>(buffer.extract<uint8_t>());
            this->wormsHealth[i] = buffer.extract<uint16_t>();
            this->positions[i * 2] = buffer.extractFloat();
            this->positions[i * 2 + 1] = buffer.extractFloat();
            this->stateIDs[i] = static_cast<Worm::StateID>(buffer.extract<uint8_t>());
        }

        for(std::size_t i = 0; i < this->num_teams; i++) {
            this->teamHealths[i] = buffer.extract<uint32_t>();
        }

        this->activePlayerWeapon = static_cast<Worm::WeaponID>(buffer.extract<uint8_t>());
        this->activePlayerAngle = buffer.extractFloat();
        this->bulletsQuantity = buffer.extract<uint8_t>();

        for(std::size_t i = 0; i < this->bulletsQuantity; i++) {
            this->bullets[i * 2] = buffer.extractFloat();
            this->bullets[i * 2 + 1] = buffer.extractFloat();
            this->bulletsAngle[i] = buffer.extractFloat();
            this->bulletType[i] = static_cast<Worm::WeaponID>(buffer.extract<uint8_t>());
        }

        for(std::size_t i = 0; i < WEAPONS_QUANTITY; i++) {
            this->weaponAmmunition[i] = buffer.extract<uint16_t>();
        }

        this->processingInputs = static_cast<bool>(buffer.extract<uint8_t>());
        this->currentPlayerTurnTime = buffer.extract<uint16_t>();
        this->gameEnded = static_cast<bool>(buffer.extract<uint8_t>());
        this->winner = buffer.extract<uint8_t>();
        this->playerUsedTool = static_cast<bool>(buffer.extract<uint8_t>());
        this->waitingForNextTurn = static_cast<bool>(buffer.extract<uint8_t>());
    }
//    std::size_t getSerializedSize() {
//        return sizeof(*this);
//    }
//
//    void serialize(void *buffer, std::size_t buffer_size) {
//        if (this->getSerializedSize() > buffer_size) {
//            throw Exception{"GameStateMsg: buffer too small"};
//        }
//
//        /* TODO: serialize each field with hton functions */
//        memcpy(buffer, this, this->getSerializedSize());
//    }
//
//    void deserialize(const void *buffer, std::size_t buffer_size) {
//        if (this->getSerializedSize() != buffer_size) {
//            throw Exception{"GameStateMsg: buffer size mismatch"};
//        }
//
//        /* TODO: deserialize each field with ntoh functions */
//        memcpy(this, buffer, this->getSerializedSize());
//    }
};
}  // namespace IO

#endif  //__GAME_STATE_MSG_H__
