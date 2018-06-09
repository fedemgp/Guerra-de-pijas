/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __GAME_H__
#define __GAME_H__

#include <atomic>
#include <list>
#include <unordered_map>

#include "Bullet.h"
#include "GameTeams.h"
#include "Observer.h"
#include "Player.h"
#include "Stage.h"

namespace Worms {
struct Teamasd {
    std::vector<uint8_t> players;
    uint8_t currentPlayer;
    bool alive;
};

class Game : Observer {
   public:
    std::atomic<bool> quit{false};

    Game(Stage &&stage);
    ~Game() {}

    Game(Game &&other) = delete;

    void start(IO::Stream<IO::GameStateMsg> *output, IO::Stream<IO::PlayerInput> *playerStream);
    void serialize(IO::Stream<IO::GameStateMsg> &s) const;
    void onNotify(const PhysicsEntity &entity, Event event) override;
    void calculateDamage(const Bullet bullet);
    void exit();

   private:
    uint8_t currentWorm;
    uint8_t currentTeam;
    double currentTurnElapsed{0};
    Physics physics;
    Stage stage;
    std::vector<Player> players;
    const double maxTurnTime;
    bool impactOnCourse{false};
    bool shotOnCourse{false};
    double currentPlayerTurnTime{0};
    bool processingClientInputs{true};
    uint8_t currentWormToFollow{0};
    bool currentPlayerShot{false};
    GameTeams teams;
    std::list<Bullet> bullets;

    std::vector<uint8_t> deadTeams;
};
}  // namespace Worms

#endif  //__GAME_H__
