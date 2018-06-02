/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <Box2D/Box2D.h>
#include <zconf.h>
#include <atomic>
#include <chrono>
#include <iostream>
#include <random>
#include <functional>
#include <algorithm>

#include "Game.h"
#include "Player.h"
#include "Stage.h"

Worms::Game::Game(Stage &&stage) : physics(b2Vec2{0.0f, -10.0f}), stage(std::move(stage)) {
    /* reserves the required space to avoid reallocations that may move the worm addresses */
    this->players.reserve(this->stage.getWorms().size());
    uint8_t id = 0;
    for (auto &wormData : this->stage.getWorms()) {
        /* initializes the instances */
        this->players.emplace_back(this->physics);
        this->players.back().setPosition(wormData.position);
        this->players.back().health = wormData.health;
        this->players.back().setId(id);
        id++;
    }

    this->makeTeams();

    /* sets the girders */
    for (auto &girder : this->stage.getGirders()) {
        b2PolygonShape poly;

        b2BodyDef bdef;
        bdef.type = b2_staticBody;
        bdef.position.Set(0.0f, 0.0f);
        b2Body *staticBody = this->physics.createBody(bdef);

        b2FixtureDef fixture;
        fixture.density = 1;
        fixture.shape = &poly;

        poly.SetAsBox(girder.length / 2, girder.height / 2, b2Vec2(girder.pos.x, girder.pos.y), 0);
        staticBody->CreateFixture(&fixture);
    }

    this->currentTeam = 0;
    this->currentWorm = this->teams[this->currentTeam].players[0];

    this->currentPlayerTurnTime = this->stage.turnTime;
}

void Worms::Game::makeTeams() {
    uint8_t numPlayers = this->players.size();
    uint8_t numTeams = this->stage.getNumTeams();

//    for (uint8_t i = 0; i < numTeams; i++) {
//        this->teams.emplace_back(Team{std::vector<uint8_t>, 0})
//    }

    std::vector<uint8_t> playersNum(numPlayers);
    for (uint8_t i = 0; i < numPlayers; i++) {
        playersNum[i] = i;
    }

    std::random_device rnd_device;
    std::mt19937 mersenne_engine(rnd_device());

    shuffle(playersNum.begin(), playersNum.end(), mersenne_engine);

    uint8_t maxTeamPlayers = (numPlayers % numTeams == 0) ? numPlayers / numTeams : numPlayers / numTeams + 1;
    std::vector<uint8_t> numPlayersPerTeam(this->stage.getNumTeams());
    for (uint8_t i = 0, nP = numPlayers, nT = numTeams; i < numPlayersPerTeam.size(); i++) {
        numPlayersPerTeam[i] = nP / nT;
        nP -= numPlayersPerTeam[i];
        nT--;
    }
    std::vector<uint8_t> players;
    for (uint8_t i = 0, currentTeam = 0; i < numPlayers; i++) {
//        this->teams[currentTeam].players.emplace_back(this->players[playersNum[i]].getId());
        players.emplace_back(this->players[playersNum[i]].getId());
        this->players[playersNum[i]].setTeam(currentTeam);
        if (numPlayersPerTeam[currentTeam] < maxTeamPlayers) {
            this->players[playersNum[i]].increaseHealth(25.0f);
        }
        if (players.size() == numPlayersPerTeam[currentTeam]) {
            this->teams.push_back(Team{players, 0, true});
            players.clear();
            currentTeam++;
        }
    }
}

void Worms::Game::start(IO::Stream<IO::GameStateMsg> *output,
                        IO::Stream<IO::PlayerInput> *playerStream) {
    try {
        /* game loop */
        std::chrono::high_resolution_clock::time_point prev =
            std::chrono::high_resolution_clock::now();
        float lag = 0.0f;
        float32 timeStep = 1.0f / 60.0f;

        while (!quit) {
            std::chrono::high_resolution_clock::time_point current =
                std::chrono::high_resolution_clock::now();
            double dt =
                std::chrono::duration_cast<std::chrono::duration<double>>(current - prev).count();
            lag += dt;

            this->currentTurnElapsed += dt;
            if (this->players[this->currentWorm].getBullet() != nullptr &&
                !this->currentPlayerShot) {
                this->currentPlayerTurnTime = 3.0f;
                this->currentTurnElapsed = 0.0f;
                this->shotOnCourse = true;
                this->currentPlayerShot = true;
            }
            if (this->currentTurnElapsed >= this->currentPlayerTurnTime) {
                bool anyWormDrowning = false;
                for (auto &worm : this->players) {
                    if (worm.getStateId() == Worm::StateID::Drown) {
                        anyWormDrowning = true;
                    }
                }
                if (!this->shotOnCourse && !anyWormDrowning) {
                    if (this->players[this->currentWorm].getStateId() != Worm::StateID::Dead) {
                        this->players[this->currentWorm].setState(Worm::StateID::Still);
                    }
                    this->currentTurnElapsed = 0;
                    this->currentPlayerShot = false;
                    this->checkTeams();
                    this->newCurrentPlayerAndTeam();

                    this->processingClientInputs = true;
                    this->currentPlayerTurnTime = this->stage.turnTime;
                } else {
                    this->processingClientInputs = false;
                    //                    this->players[this->currentWorm].setState(Worm::StateID::Still);
                }
            }

            IO::PlayerInput pi;
            if (playerStream->pop(pi, false)) {
                if (this->processingClientInputs) {
                    if (this->currentPlayerShot) {
                        if (pi != IO::PlayerInput::startShot && pi != IO::PlayerInput::endShot) {
                            this->players.at(this->currentWorm).handleState(pi);
                        }
                    } else {
                        this->players.at(this->currentWorm).handleState(pi);
                    }
                }
            }

            /* updates the actors */
            for (auto &worm : this->players) {
                worm.update(dt);
            }

            if (this->players.at(this->currentWorm).getBullet() != nullptr) {
                if (this->players.at(this->currentWorm).getBullet()->madeImpact()) {
                    DamageInfo damageInfo =
                        this->players.at(this->currentWorm).getBullet()->getDamageInfo();
                    for (auto &worm : this->players) {
                        worm.acknowledgeDamage(
                            damageInfo,
                            this->players.at(this->currentWorm).getBullet()->getPosition());
                        if (worm.getStateId() == Worm::StateID::Hit) {
                            this->impactOnCourse = true;
                        }
                    }
                    this->players[this->currentWorm].destroyBullet();
                    //                    if(this->players[this->currentWorm].getBullet() =
                    //                    nullptr){
                    //                        std::cout<<"null\n";
                    //                    } else {
                    //                        std::cout<<"not null\n";
                    //                    }
                }
            } else {
                if (!this->impactOnCourse) {
                    this->shotOnCourse = false;
                }
            }

            /* updates the physics engine */
            for (int i = 0; i < 5 && lag > timeStep; i++) {
                this->physics.update(timeStep);
                lag -= timeStep;
            }

            if (this->impactOnCourse) {
                this->impactOnCourse = false;
                this->shotOnCourse = false;
                for (size_t i = 0; i < this->players.size(); i++) {
                    Worm::StateID wormState = this->players[i].getStateId();
                    if (wormState != Worm::StateID::Still && wormState != Worm::StateID::Dead) {
                        this->impactOnCourse = true;
                        this->shotOnCourse = true;
                        this->currentWormToFollow = i;
                    }
                }
                if (!this->impactOnCourse) {
                    for (auto &worm : this->players) {
                        Worm::StateID wormState = worm.getStateId();
                        if (worm.health == 0) {
                            if (wormState != Worm::StateID::Die &&
                                wormState != Worm::StateID::Dead) {
                                worm.setState(Worm::StateID::Die);
                            }
                            if (wormState != Worm::StateID::Dead) {
                                this->impactOnCourse = true;
                                this->shotOnCourse = true;
                            }
                        }
                    }
                }
            }

            /* sends the current game state */
            this->serialize(*output);

            prev = current;
            usleep(20 * 1000);
        }

        output->close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl << "In Worms::Game::start" << std::endl;
    } catch (...) {
        std::cerr << "Unkown error in Worms::Game::start()" << std::endl;
    }
}

void Worms::Game::serialize(IO::Stream<IO::GameStateMsg> &s) const {
    assert(this->players.size() <= 20);

    IO::GameStateMsg m;
    m.num_worms = 0;
    for (const auto &worm : this->players) {
        m.positions[m.num_worms * 2] = worm.getPosition().x;
        m.positions[m.num_worms * 2 + 1] = worm.getPosition().y;
        m.stateIDs[m.num_worms] = worm.getStateId();
        m.wormsHealth[m.num_worms] = worm.health;
        m.wormsTeam[m.num_worms] = worm.getTeam();
        m.num_worms++;
    }

    /* sets the current player's data */
    m.elapsedTurnSeconds = this->currentTurnElapsed;
    m.currentPlayerTurnTime = this->currentPlayerTurnTime;
    m.currentWorm = this->currentWorm;
    m.currentWormToFollow = this->currentWormToFollow;
    m.currentTeam = this->currentTeam;
    m.activePlayerAngle = this->players[this->currentWorm].getWeaponAngle();
    m.activePlayerWeapon = this->players[this->currentWorm].getWeaponID();
    if (this->players[this->currentWorm].getBullet() != nullptr) {
        m.shoot = true;
        Math::Point<float> p = this->players[this->currentWorm].getBullet()->getPosition();
        m.bullet[0] = p.x;
        m.bullet[1] = p.y;
        m.bulletAngle = this->players[this->currentWorm].getBullet()->getAngle();
    } else {
        m.shoot = false;
        m.bullet[0] = 0;
        m.bullet[1] = 0;
        m.bulletAngle = 0;
    }

    m.processingInputs = this->processingClientInputs;

    s << m;
}

void Worms::Game::exit() {
    this->quit = true;
}

void Worms::Game::checkTeams() {
    uint8_t numTeam = 0;
    for (auto &team : this->teams) {
        if (team.alive) {
            bool teamAlive = false;
            for (auto teamPlayer : this->teams[numTeam].players) {
                if (this->players[teamPlayer].getStateId() != Worm::StateID::Dead) {
                    teamAlive = true;
                }
            }
            if (!teamAlive) {
                this->deadTeams.emplace_back(numTeam);
                team.alive = false;
            }
        }
        numTeam++;
    }
}

void Worms::Game::newCurrentPlayerAndTeam() {
    do {
        this->currentTeam = (this->currentTeam + 1) % this->teams.size();
    } while (!this->teams[this->currentTeam].alive);
    do {
        uint8_t currentTeamPlayer = this->teams[this->currentTeam].currentPlayer;
        currentTeamPlayer = (currentTeamPlayer + 1) % this->teams[this->currentTeam].players.size();
        this->teams[this->currentTeam].currentPlayer = currentTeamPlayer;
        this->currentWorm = this->teams[this->currentTeam].players[currentTeamPlayer];
//                        this->currentWorm = (this->currentWorm + 1) % this->players.size();
        this->currentWormToFollow = this->currentWorm;
    } while (this->players[this->currentWorm].getStateId() == Worm::StateID::Dead);
}
