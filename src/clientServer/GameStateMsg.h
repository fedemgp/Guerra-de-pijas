/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#ifndef __GAME_STATE_MSG_H__
#define __GAME_STATE_MSG_H__

#define WORMS_QUANTITY 20

namespace Worm {
enum class StateID { Walk, Still, StartJump, Jumping, EndJump, Bazooka
};
}

namespace IO {
enum class PlayerInput { moveNone, moveRight, moveLeft, startJump, stopMove,
    bazooka
};
// TODO protocol?
struct GameStateMsg {
    char num_worms;
    float positions[WORMS_QUANTITY * 2];
    Worm::StateID stateIDs[WORMS_QUANTITY];
};
}  // namesmpace IO

#endif  //__GAME_STATE_MSG_H__
