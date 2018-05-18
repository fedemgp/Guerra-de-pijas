/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __GAME_H__
#define __GAME_H__

#include <atomic>

#include "Player.h"
#include "World.h"

namespace Worms {

class Game {
   public:
    std::atomic<bool> quit{false};
    Game(const World &&level);
    ~Game() = default;
    void start(IO::Stream<IO::GameStateMsg> *output, IO::Stream<IO::PlayerInput> *playerStream);
    void serialize(IO::Stream<IO::GameStateMsg> &s) const;
    void exit();

   private:
    Physics physics;
    World level;
    std::vector<Player> players;
};
}  // namespace Worms

#endif  //__GAME_H__
