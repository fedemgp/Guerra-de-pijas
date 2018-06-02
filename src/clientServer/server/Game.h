/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __GAME_H__
#define __GAME_H__

#include <atomic>

#include "Player.h"
#include "Stage.h"

namespace Worms {

class Game {
   public:
    std::atomic<bool> quit{false};

    Game(Stage &&stage);
    ~Game() {}

    Game(Game &&other) = delete;

    void start(IO::Stream<IO::GameStateMsg> *output, IO::Stream<IO::PlayerInput> *playerStream);
    void serialize(IO::Stream<IO::GameStateMsg> &s) const;
    void exit();

   private:
    char currentWorm{0};
    double currentTurnElapsed{0};
    Physics physics;
    Stage stage;
    std::vector<Player> players;
    const double maxTurnTime;
    bool impactOnCourse{false};
    bool shotOnCourse{false};
    double currentPlayerTurnTime{0};
    bool processingClientInputs{true};
    char currentWormToFollow{0};
    bool currentPlayerShot{false};
};
}  // namespace Worms

#endif  //__GAME_H__
