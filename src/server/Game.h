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
#include "GameClock.h"
#include "GameTurn.h"

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
    void onNotify(Subject &subject, Event event) override;
    void calculateDamage(const Bullet &bullet);
    void exit();
    void endTurn();

   private:
    void inputWorker(std::size_t playerIndex);
    void outputWorker(std::size_t playerIndex);

    uint8_t currentWorm;
    uint8_t currentTeam;
    Physics physics;
    Stage stage;
    std::vector<Player> players;
    const double maxTurnTime;
    bool processingClientInputs{true};
    uint8_t currentWormToFollow{0};
    bool currentPlayerShot{false};
    GameTeams teams;
    std::list<Bullet> bullets;

    std::vector<uint8_t> deadTeams;
    GameClock gameClock;
    GameTurn gameTurn;

    /* communication */
    std::vector<std::thread> inputThreads;
    std::vector<std::thread> outputThreads;
    std::vector<CommunicationSocket> &sockets;
    std::vector<PlayerInput> inputs;
    IO::DoubleBuffer<IO::GameStateMsg> snapshot;
    bool removeBullets{false};
};
}  // namespace Worms

#endif  //__GAME_H__
