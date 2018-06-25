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

// TODO move this in client and Server global Config

#define POWER_CHARGE_TIME 5.0f

#define COMMAND_GET_LEVELS 0
#define COMMAND_JOIN_GAME 1
#define COMMAND_GET_GAMES 2
#define COMMAND_CREATE_GAME 3
#define COMMAND_QUIT 5

#include <stdint.h>
#include <cstring>
#include <netinet/in.h>
#include <stdint.h>
#include <vector>

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
        std::string name;
        uint8_t playersQuantity;
    };

    struct GameInfo {
        uint8_t gameID;
        uint8_t numCurrentPlayers;
        uint8_t numTotalPlayers;
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

    std::size_t getSerializedSize() {
        std::size_t length(0);
        length += sizeof(input);
        length += sizeof(position.x);
        length += sizeof(position.y);

        return length;
    }

    void serialize(void *buffer, std::size_t buffer_size) {
        if (this->getSerializedSize() > buffer_size) {
            throw Exception{"PlayerMsg: buffer too small"};
        }

        /* TODO: serialize each field with hton functions */
        memcpy(buffer, this, this->getSerializedSize());
    }

    void deserialize(const void *buffer, std::size_t buffer_size) {
        if (this->getSerializedSize() != buffer_size) {
            throw Exception{"PlayerMsg: buffer size mismatch"};
        }

        /* TODO: deserialize each field with ntoh functions */
        memcpy(this, buffer, this->getSerializedSize());
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
    float wormsHealth[WORMS_QUANTITY];
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

    std::size_t getSerializedSize() {
        return sizeof(*this);
    }

    void serialize(void *buffer, std::size_t buffer_size) {
        if (this->getSerializedSize() > buffer_size) {
            throw Exception{"GameStateMsg: buffer too small"};
        }

        /* TODO: serialize each field with hton functions */
        memcpy(buffer, this, this->getSerializedSize());
    }

    void deserialize(const void *buffer, std::size_t buffer_size) {
        if (this->getSerializedSize() != buffer_size) {
            throw Exception{"GameStateMsg: buffer size mismatch"};
        }

        /* TODO: deserialize each field with ntoh functions */
        memcpy(this, buffer, this->getSerializedSize());
    }
};
}  // namespace IO

#endif  //__GAME_STATE_MSG_H__
