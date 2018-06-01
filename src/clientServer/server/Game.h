/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __GAME_H__
#define __GAME_H__

#include <atomic>
#include <unordered_map>

#include "Player.h"
#include "Stage.h"

namespace Worms {
struct Team {
    std::vector<uint8_t> players;
    uint8_t currentPlayer;
};

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
    void makeTeams();

    char currentWorm{0};
    char currentTeam{0};
    double currentTurnElapsed{0};
    Physics physics;
    Stage stage;
    std::vector<Player> players;
    bool impactOnCourse{false};
    bool shotOnCourse{false};
    double currentPlayerTurnTime{0};
    bool processingClientInputs{true};
    char currentWormToFollow{0};
    bool currentPlayerShot{false};
    std::vector<Team> teams;
};
}  // namespace Worms

#endif  //__GAME_H__
