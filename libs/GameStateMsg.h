/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#ifndef __GAME_STATE_MSG_H__
#define __GAME_STATE_MSG_H__

#define WORMS_QUANTITY 20

#include <stdint.h>

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
    Bazooka,
    Hit,
    Die,
    Dead
};
}

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
    endShot
};
// TODO protocol?
struct GameStateMsg {
    uint8_t elapsedTurnSeconds;
    uint8_t currentWorm;
    uint8_t num_worms;
    float positions[WORMS_QUANTITY * 2];
    Worm::StateID stateIDs[WORMS_QUANTITY];
    float activePlayerAngle;
    bool shoot;
    float bullet[2];
    float bulletAngle;
    float life[WORMS_QUANTITY];
    bool processingInputs;
};
}  // namespace IO

#endif  //__GAME_STATE_MSG_H__
