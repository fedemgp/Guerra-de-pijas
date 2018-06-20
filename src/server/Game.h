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
#include "GameClock.h"
#include "GameTeams.h"
#include "GameTurn.h"
#include "Girder.h"
#include "Observer.h"
#include "Player.h"
#include "Stage.h"

namespace Worms {
using PlayerInput = IO::Stream<IO::PlayerMsg>;
using GameSnapshot = IO::DoubleBuffer<IO::GameStateMsg>;

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
    /**
     * @brief calculates damage for weapons that throw bullets. It gives
     * information of the bullet to all players so them can calculate his damage
     * and apply an impulse if this was hitted.
     * @param bullet
     */
    void calculateDamage(const Bullet &bullet);
    /**
     * @brief calculates damage for p2p weapons (baseball). It gives
     * information of the weapon (direction, point and damageInfo) to the
     * players so that they can calculate his damage and apply an impulse if
     * this was hitted.
     * @param weapon
     */
    void calculateDamage(std::shared_ptr<Worms::Weapon> weapon, Math::Point<float> shooterPosition,
                         Direction shooterDirection);
    void calculateWind();
    void exit();
    void endTurn();

   private:
    void inputWorker(std::size_t playerIndex);
    void outputWorker(std::size_t playerIndex);

    uint8_t currentWorm;
    uint8_t currentTeam{0};
    Physics physics;
    Stage stage;
    std::vector<Girder> girders;
    std::vector<Player> players;
    const double maxTurnTime;
    bool processingClientInputs{true};
    uint8_t currentWormToFollow{0};
    bool currentPlayerShot{false};
    GameTeams teams;
    std::list<Bullet> bullets;
    Worms::Wind wind;

    std::vector<uint8_t> deadTeams;
    GameClock gameClock;
    GameTurn gameTurn;

    /* communication */
    std::vector<std::thread> inputThreads;
    std::vector<std::thread> outputThreads;
    std::vector<CommunicationSocket> &sockets;
    std::vector<PlayerInput> inputs;
    std::vector<GameSnapshot> snapshots;
    std::uint8_t playersConnected;
    bool removeBullets{false};
    bool gameEnded{false};
    std::uint8_t winnerTeam{0};

    void playerDisconnected();
};
}  // namespace Worms

#endif  //__GAME_H__
