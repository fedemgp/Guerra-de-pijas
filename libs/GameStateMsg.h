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
        YAML::Emitter emitter;
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "in" << YAML::Value << static_cast<std::uint32_t>(this->input);
        emitter << YAML::Key << "pos" << YAML::Value;
        {
            emitter << YAML::BeginMap;
            emitter << YAML::Key << "x" << YAML::Value << this->position.x;
            emitter << YAML::Key << "y" << YAML::Value << this->position.y;
            emitter << YAML::EndMap;
        }
        emitter << YAML::EndMap;
        return std::move(std::string(emitter.c_str()));
    }

    void deserialize(const std::string &data) {
        YAML::Node msg = YAML::Load(data);
        if (!msg["pos"] || !msg["in"] || !msg["pos"]["x"].IsScalar() ||
            !msg["pos"]["y"].IsScalar()) {
            throw Exception("PlayerMsg: data corrupted");
        }

        this->position.x = msg["pos"]["x"].as<float>();
        this->position.y = msg["pos"]["y"].as<float>();

        this->input = static_cast<PlayerInput>(msg["in"].as<std::uint32_t>());
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
        YAML::Emitter emitter;
        emitter << YAML::BeginMap;
        emitter << YAML::Key << ELAPSED_TURN << YAML::Value << this->elapsedTurnSeconds;
        emitter << YAML::Key << WIND_INTENSITY << YAML::Value << (int) this->windIntensity;
        emitter << YAML::Key << CURRENT_WORM << YAML::Value << this->currentWorm;
        emitter << YAML::Key << CURRENT_WORM_TO_FOLLOW << YAML::Value << this->currentWormToFollow;
        emitter << YAML::Key << CURRENT_TEAM << YAML::Value << this->currentTeam;
        emitter << YAML::Key << NUM_WORMS << YAML::Value << this->num_worms;
        emitter << YAML::Key << NUM_TEAMS_KEY << YAML::Value << this->num_teams;

        emitter << YAML::Key << WORMS_TEAM << YAML::Value << YAML::BeginSeq;
        for (int i = 0; i < WORMS_QUANTITY; i++) {
            emitter << this->wormsTeam[i];
        }
        emitter << YAML::EndSeq;

        emitter << YAML::Key << WORM_DIRECTION << YAML::Value << YAML::BeginSeq;
        for (int i = 0; i < WORMS_QUANTITY; i++) {
            emitter << static_cast<std::uint8_t>(this->wormsDirection[i]);
        }
        emitter << YAML::EndSeq;

        emitter << YAML::Key << WORM_HEALTH_KEY << YAML::Value << YAML::BeginSeq;
        for (int i = 0; i < WORMS_QUANTITY; i++) {
            emitter << this->wormsHealth[i];
        }
        emitter << YAML::EndSeq;

        emitter << YAML::Key << TEAM_HEALTHS << YAML::Value << YAML::BeginSeq;
        for (int i = 0; i < TOTAL_TEAM_QUANTITY; i++) {
            emitter << this->teamHealths[i];
        }
        emitter << YAML::EndSeq;

        emitter << YAML::Key << WORM_POSITION << YAML::Value << YAML::BeginSeq;
        int totalPos = WORMS_QUANTITY * 2;
        for (int i = 0; i < totalPos; i++) {
            emitter << this->positions[i];
        }
        emitter << YAML::EndSeq;

        emitter << YAML::Key << WORM_STATES << YAML::Value << YAML::BeginSeq;
        for (int i = 0; i < WORMS_QUANTITY; i++) {
            emitter << static_cast<std::uint8_t>(this->stateIDs[i]);
        }
        emitter << YAML::EndSeq;

        emitter << YAML::Key << CURRENT_WEAPON << YAML::Value
                << static_cast<std::uint8_t>(this->activePlayerWeapon);
        emitter << YAML::Key << WORM_ANGLES << YAML::Value << this->activePlayerAngle;
        emitter << YAML::Key << BULLET_QUANTITY_KEY << YAML::Value << this->bulletsQuantity;

        emitter << YAML::Key << BULLET_POSITION << YAML::Value << YAML::BeginSeq;
        int totalBullPos = BULLETS_QUANTITY * 2;
        for (int i = 0; i < totalBullPos; i++) {
            emitter << this->bullets[i];
        }
        emitter << YAML::EndSeq;

        emitter << YAML::Key << BULLET_ANGLES << YAML::Value << YAML::BeginSeq;
        for (int i = 0; i < BULLETS_QUANTITY; i++) {
            emitter << this->bulletsAngle[i];
        }
        emitter << YAML::EndSeq;

        emitter << YAML::Key << BULLET_TYPES << YAML::Value << YAML::BeginSeq;
        for (int i = 0; i < BULLETS_QUANTITY; i++) {
            emitter << static_cast<std::uint8_t>(this->bulletType[i]);
        }
        emitter << YAML::EndSeq;

        emitter << YAML::Key << WEAPON_AMMUNITION << YAML::Value << YAML::BeginSeq;
        for (int i = 0; i < WEAPONS_QUANTITY; i++) {
            emitter << this->weaponAmmunition[i];
        }
        emitter << YAML::EndSeq;

        emitter << YAML::Key << PROCESSING_INPUTS << YAML::Value << this->processingInputs;
        emitter << YAML::Key << CURRENT_TURN_TIME << YAML::Value << this->currentPlayerTurnTime;
        emitter << YAML::Key << GAME_ENDED << YAML::Value << this->gameEnded;
        emitter << YAML::Key << WINNER << YAML::Value << this->winner;
        emitter << YAML::Key << USED_TOOL << YAML::Value << this->playerUsedTool;
        emitter << YAML::Key << WAITING_FOR_NEXT_TURN << YAML::Value << this->waitingForNextTurn;

        emitter << YAML::EndMap;

        return std::move(std::string(emitter.c_str()));
    }

    void deserialize(const std::string &data) {
        YAML::Node msg = YAML::Load(data);

        this->elapsedTurnSeconds = msg[ELAPSED_TURN].as<std::uint16_t>();
        this->windIntensity = static_cast<std::int8_t >(msg[WIND_INTENSITY].as<int>());
        this->currentWorm = msg[CURRENT_WORM].as<std::uint8_t>();
        this->currentWormToFollow = msg[CURRENT_WORM_TO_FOLLOW].as<std::uint8_t>();
        this->currentTeam = msg[CURRENT_TEAM].as<std::uint8_t>();
        this->num_worms = msg[NUM_WORMS].as<std::uint8_t>();
        this->num_teams = msg[NUM_TEAMS_KEY].as<std::uint8_t>();
        this->activePlayerWeapon =
            static_cast<Worm::WeaponID>(msg[CURRENT_WEAPON].as<std::uint8_t>());
        this->activePlayerAngle = msg[WORM_ANGLES].as<float>();
        this->bulletsQuantity = msg[BULLET_QUANTITY_KEY].as<std::uint8_t>();
        this->processingInputs = msg[PROCESSING_INPUTS].as<bool>();
        this->currentPlayerTurnTime = msg[CURRENT_TURN_TIME].as<std::uint16_t>();
        this->gameEnded = msg[GAME_ENDED].as<bool>();
        this->winner = msg[WINNER].as<std::uint8_t>();
        this->playerUsedTool = msg[USED_TOOL].as<bool>();
        this->waitingForNextTurn = msg[WAITING_FOR_NEXT_TURN].as<bool>();

        for (int i = 0, j = 0; i < WORMS_QUANTITY; i++, j += 2) {
            this->wormsTeam[i] = msg[WORMS_TEAM][i].as<std::uint8_t>();
            this->wormsDirection[i] =
                static_cast<Worm::Direction>(msg[WORM_DIRECTION][i].as<std::uint8_t>());
            this->wormsHealth[i] = msg[WORM_HEALTH_KEY][i].as<std::uint16_t>();
            this->positions[j] = msg[WORM_POSITION][j].as<float>();
            this->positions[j + 1] = msg[WORM_POSITION][j + 1].as<float>();
            this->stateIDs[i] = static_cast<Worm::StateID>(msg[WORM_STATES][i].as<std::uint8_t>());
        }

        for (int i = 0, j = 0; i < BULLETS_QUANTITY; i++, j += 2) {
            this->bullets[j] = msg[BULLET_POSITION][j].as<float>();
            this->bullets[j + 1] = msg[BULLET_POSITION][j + 1].as<float>();
            this->bulletsAngle[i] = msg[BULLET_ANGLES][i].as<float>();
            this->bulletType[i] =
                static_cast<Worm::WeaponID>(msg[BULLET_TYPES][i].as<std::uint8_t>());
        }

        for (int i = 0; i < WEAPONS_QUANTITY; i++) {
            this->weaponAmmunition[i] = msg[WEAPON_AMMUNITION][i].as<std::int16_t>();
        }

        for (int i = 0; i < TOTAL_TEAM_QUANTITY; i++) {
            this->teamHealths[i] = msg[TEAM_HEALTHS][i].as<std::uint32_t>();
        }
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
