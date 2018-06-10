/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __GAME_H__
#define __GAME_H__

#include <atomic>
#include <list>
#include <thread>
#include <unordered_map>

#include "Bullet.h"
#include "CommunicationSocket.h"
#include "DoubleBuffer.h"
#include "GameTeams.h"
#include "Observer.h"
#include "Player.h"
#include "Stage.h"

namespace Worms {
using PlayerInput = IO::Stream<IO::PlayerMsg>;

struct Teamasd {
    std::vector<uint8_t> players;
    uint8_t currentPlayer;
    bool alive;
};

class Game : Observer {
   public:
    std::atomic<bool> quit{false};

    Game(Stage &&stage, std::vector<CommunicationSocket> &sockets);
    virtual ~Game();

    Game(Game &&other) = delete;

    void start();
    IO::GameStateMsg serialize() const;
    void onNotify(const PhysicsEntity &entity, Event event) override;
    void calculateDamage(const Bullet &bullet);
    void exit();

   private:
    void inputWorker(std::size_t playerIndex);
    void outputWorker(std::size_t playerIndex);

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
    uint8_t drowningWormsQuantity{0};

    /* communication */
    std::vector<std::thread> inputThreads;
    std::vector<std::thread> outputThreads;
    std::vector<CommunicationSocket> &sockets;
    std::vector<PlayerInput> inputs;
    IO::DoubleBuffer<IO::GameStateMsg> snapshot;
};
}  // namespace Worms

#endif  //__GAME_H__
