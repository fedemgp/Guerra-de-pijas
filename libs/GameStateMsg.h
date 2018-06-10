/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#ifndef __GAME_STATE_MSG_H__
#define __GAME_STATE_MSG_H__

#define WORMS_QUANTITY 20
#define BULLETS_QUANTITY 7
// TODO move this in client and Server global Config
#define POWER_CHARGE_TIME 5.0f

#include <stdint.h>

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
    Land
};
enum WeaponID { WNone, WBazooka, WGrenade, WCluster, WMortar, WBanana, WHoly,
    WExplode, WFragment
};
}  // namespace Worm

namespace IO {
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
    selectedPosition
};
struct PlayerMsg{
    PlayerInput input;
    Math::Point<float> position{0.0f, 0.0f};
};
// TODO protocol?
struct GameStateMsg {
    double elapsedTurnSeconds;
    uint8_t currentWorm;
    uint8_t currentWormToFollow;
    uint8_t num_worms;
    uint8_t wormsTeam[WORMS_QUANTITY];
    float wormsHealth[WORMS_QUANTITY];
    float positions[WORMS_QUANTITY * 2];
    Worm::StateID stateIDs[WORMS_QUANTITY];
    Worm::WeaponID activePlayerWeapon;
    float activePlayerAngle;
    uint8_t bulletsQuantity;
    float bullets[2 * BULLETS_QUANTITY];
    float bulletsAngle[BULLETS_QUANTITY];
    Worm::WeaponID bulletType[BULLETS_QUANTITY];

    bool processingInputs;
    double currentPlayerTurnTime;
    char currentTeam;
};
}  // namespace IO

#endif  //__GAME_STATE_MSG_H__
