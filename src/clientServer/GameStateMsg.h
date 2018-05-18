/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#ifndef __GAME_STATE_MSG_H__
#define __GAME_STATE_MSG_H__

namespace IO {
// TODO protocol?
struct GameStateMsg {
    char num_worms;
    float positions[20 * 2];
};

enum class PlayerInput {
    move_right,
    move_left,
    stop_move,
};
}  // namesmpace IO

#endif  //__GAME_STATE_MSG_H__
