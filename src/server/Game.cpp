/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <Stage.h>
#include <zconf.h>
#include <atomic>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include "Box2D/Box2D.h"
#include "Chronometer.h"

#include "Config/Config.h"
#include "Direction.h"
#include "Game.h"
#include "GameStates/ImpactOnCourse.h"
#include "Player.h"
#include "Stage.h"
#include "Weapons/BaseballBat.h"

#define CONFIG ::Game::Config::getInstance()
#define TIME_STEP (1.0f / 60.0f)

Worms::Game::Game(Stage &&stage, std::vector<CommunicationSocket> &sockets)
    : physics(b2Vec2{0.0f, -10.0f}, TIME_STEP),
      stage(std::move(stage)),
      maxTurnTime(::Game::Config::getInstance().getExtraTurnTime()),
      gameTurn(*this),
      sockets(sockets),
      inputs(sockets.size()),
      snapshots(sockets.size()) {
    this->inputThreads.reserve(sockets.size());
    this->outputThreads.reserve(sockets.size());
    for (std::size_t i = 0; i < sockets.size(); i++) {
        this->inputThreads.emplace_back([this, i] { this->inputWorker(i); });
        this->outputThreads.emplace_back([this, i] { this->outputWorker(i); });
    }
    /* reserves the required space to avoid reallocations that may move the worm addresses */
    this->players.reserve(this->stage.getWorms().size());
    uint8_t id = 0;
    for (auto &wormData : this->stage.getWorms()) {
        /* initializes the instances */
        this->players.emplace_back(this->physics);
        this->players.back().setPosition(wormData.position);
        this->players.back().health = wormData.health;
        this->players.back().setId(id);
        this->players.back().addObserver(this);
        id++;
    }

    this->teams.makeTeams(this->players, (uint8_t)sockets.size(), this->stage.getAmmoCounter());
    //    this->wind.range = CONFIG.getWindIntensityRange();
    this->wind.minIntensity = CONFIG.getMinWindIntensity();
    this->wind.maxIntensity = CONFIG.getMaxWindIntensity();
    this->calculateWind();

    /* sets the girders */
    this->girders.reserve(this->stage.getGirders().size());
    for (auto &girder : this->stage.getGirders()) {
        this->girders.emplace_back(girder, this->physics);
    }

    /* calculate the initial team's healths */
    this->teamHealths = this->teams.getTotalHealth(this->players);

    this->currentWorm = this->teams.getCurrentPlayerID();
    this->currentWormToFollow = this->currentWorm;

    this->gameClock.addObserver(this);
    this->gameClock.waitForNextTurn();
}

Worms::Game::~Game() {
    this->exit();
    for (auto &t : this->outputThreads) {
        t.join();
    }

    for (auto &t : this->inputThreads) {
        t.join();
    }
}

/**
 * @brief Reads player messages from a socket and pushes them into the input queue.
 *
 * @param playerIndex The index of the player.
 */
void Worms::Game::inputWorker(std::size_t playerIndex) {
    PlayerInput &input = this->inputs.at(playerIndex);
    CommunicationSocket &socket = this->sockets.at(playerIndex);

    /* TODO: avoid hardcoding the size */
    IO::PlayerMsg msg;

    try {
        while (!this->quit) {
            /* receives the size of the msg */
            std::uint32_t size(0);
            socket.receive((char *)&size, sizeof(std::uint32_t));
            size = ntohl(size);

            std::vector<char> buffer(size, 0);
            /* reads the raw data from the buffer */
            socket.receive(buffer.data(), size);

            std::string buff(buffer.data(), size);

            /* sets the struct data from the buffer */
            msg.deserialize(buff);

            /* pushes the message into the player's input queue if it's the current player */
            if (this->currentTeam == playerIndex) {
                input.push(msg);
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Worms::Game::inputWorker:" << e.what() << std::endl;
    }
}

/**
 * @brief Sends model snapshot messages to a socket.
 *
 * @param playerIndex The index of the player to send the spanshots to.
 */
void Worms::Game::outputWorker(std::size_t playerIndex) {
    CommunicationSocket &socket = this->sockets.at(playerIndex);
    GameSnapshot &snapshot = this->snapshots.at(playerIndex);

    IO::GameStateMsg msg;

    try {
        while (!this->quit) {
            msg = snapshot.get(true);
            std::string buff = msg.serialize();
            std::uint32_t size = buff.size();
            std::uint32_t netInt = htonl(size);

            socket.send((char *)&netInt, sizeof(std::uint32_t));
            socket.send(buff.data(), size);
        }
    } catch (const IO::Interrupted &e) {
        /* this means that the game is ready to exit */
    } catch (const std::exception &e) {
        std::cerr << "Worms::Game::outputWorker:" << e.what() << std::endl;
    }
}

void Worms::Game::start() {
    try {
        /* game loop */
        Utils::Chronometer chronometer;
        while (!quit) {
            double dt = chronometer.elapsed();

            this->gameClock.update(dt);
            this->gameTurn.update(dt);

            IO::PlayerMsg pMsg;
            if (this->inputs.at(this->currentTeam).pop(pMsg, false)) {
                if (this->processingClientInputs) {
                    if (this->currentPlayerShot) {
                        if (pMsg.input != IO::PlayerInput::startShot &&
                            pMsg.input != IO::PlayerInput::endShot &&
                            pMsg.input != IO::PlayerInput::positionSelected) {
                            this->players.at(this->currentWorm).handleState(pMsg);
                        }
                    } else {
                        this->players.at(this->currentWorm).handleState(pMsg);
                    }
                }
            }

            /* updates the actors */
            for (auto &worm : this->players) {
                worm.update(dt);
            }

            for (auto &bullet : this->bullets) {
                bullet.update(dt, this->wind);
            }

            this->physics.update(dt);

            /* serializes and updates the game state */
            auto msg = this->serialize();
            for (auto &snapshot : this->snapshots) {
                snapshot.set(msg);
                snapshot.swap();
            }

            if (this->gameEnded) {
                this->quit = true;
            }

            if (TIME_STEP > dt) {
                usleep((TIME_STEP - dt) * 1000000);
            }
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl << "In Worms::Game::start" << std::endl;
    } catch (...) {
        std::cerr << "Unkown error in Worms::Game::start()" << std::endl;
    }
}

void Worms::Game::endTurn() {
    this->waitingForNextTurn = false;
    this->processingClientInputs = true;
    this->gameClock.restart();
    this->gameTurn.restart();
    this->calculateWind();
}

void Worms::Game::calculateCurrentPlayer() {
    this->waitingForNextTurn = true;
    this->players[this->currentWorm].reset();
    this->gameEnded = this->teams.endTurn(this->players);
    if (this->gameEnded) {
        this->winnerTeam = this->teams.getWinner();
    }
    this->currentTeam = this->teams.getCurrentTeamID();
    this->currentWorm = this->teams.getCurrentPlayerID();
    this->currentWormToFollow = this->currentWorm;
}

IO::GameStateMsg Worms::Game::serialize() const {
    assert(this->players.size() <= 20);

    IO::GameStateMsg m;
    memset(&m, 0, sizeof(m));

    m.num_worms = 0;
    m.num_teams = this->teams.getTeamQuantity();
    for (const auto &worm : this->players) {
        m.positions[m.num_worms * 2] = worm.getPosition().x;
        m.positions[m.num_worms * 2 + 1] = worm.getPosition().y;
        m.stateIDs[m.num_worms] = worm.getStateId();
        m.wormsHealth[m.num_worms] = worm.health;
        m.wormsTeam[m.num_worms] = worm.getTeam();
        m.wormsDirection[m.num_worms] = worm.direction;
        m.num_worms++;
    }

    /* sets team health*/
    uint8_t i{0};
    for (auto health : this->teamHealths) {
        m.teamHealths[i++] = health;
    }
    /* sets wind data */
    m.windIntensity =
        (char)(127.0f * this->wind.instensity /
               (this->wind.maxIntensity - this->wind.minIntensity) * this->wind.xDirection);

    /* sets the current player's data */
    m.elapsedTurnSeconds = static_cast<std::uint16_t>(std::floor(this->gameClock.getTimeElapsed()));
    m.currentPlayerTurnTime = static_cast<std::uint16_t>(std::floor(this->gameClock.getTurnTime()));
    m.currentWorm = this->currentWorm;
    m.currentWormToFollow = this->currentWormToFollow;
    m.currentTeam = this->currentTeam;
    m.activePlayerAngle = this->players[this->currentWorm].getWeaponAngle();
    m.activePlayerWeapon = this->players[this->currentWorm].getWeaponID();

    m.bulletsQuantity = this->bullets.size();
    i = 0;
    uint8_t j = 0;
    for (auto &bullet : this->bullets) {
        Math::Point<float> p = bullet.getPosition();
        m.bullets[i++] = p.x;
        m.bullets[i++] = p.y;
        m.bulletsAngle[j] = bullet.getAngle();
        m.bulletType[j++] = bullet.getWeaponID();
    }
    /*
     * serialize the ammunition counter
     */
    this->teams.serialize(m);
    m.processingInputs = this->processingClientInputs;
    m.playerUsedTool = this->currentPlayerShot;
    m.waitingForNextTurn = this->waitingForNextTurn;
    m.gameEnded = this->gameEnded;
    m.winner = this->winnerTeam;

    return m;
}

void Worms::Game::exit() {
    this->quit = true;
    for (auto &snapshot : this->snapshots) {
        snapshot.interrupt();
    }
    for (auto &socket : this->sockets) {
        socket.shutdown();
    }
}

void Worms::Game::onNotify(Subject &subject, Event event) {
    switch (event) {
        /**
         * Because i didnt want to move all responsability of the bullets to
         * the game (until the refactor of the start), i added this function
         * that delegates to the player the responsability to iterate all over
         * the bullets and add the game as an observer
         */
        case Event::Shot: {
            //             this->players[this->currentWorm].addObserverToBullets(this);
            this->bullets.merge(this->players[this->currentWorm].getBullets());
            for (auto &bullet : this->bullets) {
                bullet.addObserver(this);
            }
            this->gameClock.playerShot();
            this->gameTurn.playerShot(this->players[this->currentWorm].getWeaponID());
            this->currentPlayerShot = true;
            break;
        }
        /**
         * On explode, the game must check worms health.
         */
        case Event::Explode: {
            auto &bullet = dynamic_cast<const Bullet &>(subject);
            this->gameTurn.explosion();
            this->calculateDamage(bullet);
            break;
        }
        case Event::P2PWeaponUsed: {
            auto &player = dynamic_cast<const Worms::Player &>(subject);
            const std::shared_ptr<Worms::Weapon> weapon = player.getWeapon();
            this->gameClock.playerShot();
            this->gameTurn.playerShot(this->players[this->currentWorm].getWeaponID());
            this->currentPlayerShot = true;
            this->gameTurn.explosion();
            this->calculateDamage(weapon, player.getPosition(), player.direction);
            break;
        }
        /**
         * onExplode will create new Bullets in player's container, and we
         * need to listen to them.
         */
        case Event::OnExplode: {
            auto &bullet = dynamic_cast<const Bullet &>(subject);
            this->calculateDamage(bullet);

            this->bullets.merge(this->players[this->currentWorm].onExplode(bullet, this->physics));

            for (auto &fragment : this->bullets) {
                fragment.addObserver(this);
            }
            //            this->players[this->currentWorm].addObserverToBullets(this);
            break;
        }
        case Event::Teleported: {
            this->gameClock.playerShot();
            this->currentPlayerShot = true;
            this->teams.weaponUsed(this->players[this->currentWorm].getWeaponID());
        }
        case Event::WormFalling: {
            this->gameTurn.wormFalling(dynamic_cast<const Player &>(subject).getId());
            break;
        }
        case Event::WormLanded: {
            this->gameTurn.wormLanded(dynamic_cast<const Player &>(subject).getId());
            break;
        }
        case Event::Hit: {
            this->gameTurn.wormHit(dynamic_cast<const Player &>(subject).getId());
            break;
        }
        case Event::EndHit: {
            this->gameTurn.wormEndHit(dynamic_cast<const Player &>(subject).getId());
            break;
        }
        case Event::Drowning: {
            this->gameTurn.wormDrowning(dynamic_cast<const Player &>(subject).getId());
            break;
        }
        case Event::Drowned: {
            this->gameTurn.wormDrowned(dynamic_cast<const Player &>(subject).getId());
            break;
        }
        case Event::Dying: {
            this->gameTurn.wormDying();
            break;
        }
        case Event::Dead: {
            this->gameTurn.wormDead();
            this->gameTurn.endTurn();
            break;
        }
        case Event::NewWormToFollow: {
            this->currentWormToFollow =
                dynamic_cast<const ImpactOnCourse &>(subject).getWormToFollow();
            break;
        }
        case Event::DamageOnLanding: {
            this->gameClock.endTurn();
            break;
        }
        case Event::ImpactEnd: {
            auto &wormsHit = dynamic_cast<ImpactOnCourse &>(subject).getWormsHit();
            for (auto worm : wormsHit) {
                Worm::StateID wormState = this->players[worm].getStateId();
                if (this->players[worm].health == 0) {
                    if (wormState != Worm::StateID::Die && wormState != Worm::StateID::Dead) {
                        this->players[worm].setState(Worm::StateID::Die);
                    }
                }
            }
            break;
        }
        case Event::EndTurn: {
            this->processingClientInputs = false;
            this->gameTurn.endTurn();
            break;
        }
        case Event::TurnEnded: {
            if (this->players[this->currentWorm].getStateId() != Worm::StateID::Dead) {
                this->players[this->currentWorm].setState(Worm::StateID::Still);
            }
            this->bullets.erase(this->bullets.begin(), this->bullets.end());
            this->gameClock.waitForNextTurn();
            this->teamHealths = this->teams.getTotalHealth(this->players);
            this->calculateCurrentPlayer();
            break;
        }
        case Event::NextTurn: {
            this->currentPlayerShot = false;
            this->endTurn();
            break;
        }
    }
}

void Worms::Game::calculateDamage(const Worms::Bullet &bullet) {
    Config::Bullet::DamageInfo damageInfo = bullet.getDamageInfo();
    for (auto &worm : this->players) {
        worm.acknowledgeDamage(damageInfo, bullet.getPosition());
    }
    this->removeBullets = true;
}
/**
 * @brief calculate damage for p2p weapons. Because the only one is the
 * baseball bat and because we are running out of time, there will be
 * a cast to a baseballWeapon.
 * TODO make a class between weapon and baseballBat, that represents a
 * p2pWeapon.
 * @param weapon
 */
void Worms::Game::calculateDamage(std::shared_ptr<Worms::Weapon> weapon,
                                  Math::Point<float> shooterPosition,
                                  Worm::Direction shooterDirection) {
    auto *baseball = (::Weapon::BaseballBat *)weapon.get();
    Config::P2PWeapon &weaponInfo = baseball->getWeaponInfo();
    for (auto &worm : this->players) {
        worm.acknowledgeDamage(weaponInfo, shooterPosition, shooterDirection);
    }
    this->removeBullets = true;
}

void Worms::Game::calculateWind() {
        std::random_device rnd_device;
        std::mt19937 mersenne_engine(rnd_device());
        std::uniform_real_distribution<> distr(this->wind.minIntensity, this->wind.maxIntensity);

        this->wind.xDirection =
            (distr(mersenne_engine) > (this->wind.maxIntensity - this->wind.minIntensity) / 2.0f)
            ? 1
                                                                                                  : -1;
        this->wind.instensity = (float) distr(mersenne_engine);
}
