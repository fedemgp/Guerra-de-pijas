/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <zconf.h>
#include <atomic>
#include <chrono>
#include <iostream>
#include "Box2D/Box2D.h"
#include "Chronometer.h"
//#include <random>

#include "Config.h"
#include "Game.h"
#include "Player.h"
#include "Stage.h"

Worms::Game::Game(Stage &&stage, std::vector<CommunicationSocket> &sockets)
    : physics(b2Vec2{0.0f, -10.0f}),
      stage(std::move(stage)),
      maxTurnTime(::Game::Config::getInstance().getExtraTurnTime()),
      sockets(sockets),
      inputs(sockets.size()) {
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

    this->teams.makeTeams(this->players, (uint8_t)sockets.size());

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

    this->currentWorm = this->teams.getCurrentPlayerID();
    this->currentWormToFollow = this->currentWorm;

    this->currentPlayerTurnTime = this->stage.turnTime;
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
    char *buffer = new char[msg.getSerializedSize()];

    try {
        while (!this->quit) {
            /* reads the raw data from the buffer */
            socket.receive(buffer, msg.getSerializedSize());

            /* sets the struct data from the buffer */
            msg.deserialize(buffer, msg.getSerializedSize());

            /* pushes the message into the player's input queue if it's the current player */
            if (this->currentTeam == playerIndex) {
                input.push(msg);
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Worms::Game::inputWorker:" << e.what() << std::endl;
        this->quit = true;
    }

    delete buffer;
}

/**
 * @brief Sends model snapshot messages to a socket.
 *
 * @param playerIndex The index of the player to send the spanshots to.
 */
void Worms::Game::outputWorker(std::size_t playerIndex) {
    CommunicationSocket &socket = this->sockets.at(playerIndex);

    IO::GameStateMsg msg;
    char *buffer = new char[msg.getSerializedSize()];

    try {
        while (!this->quit) {
            msg = this->snapshot.get(true);
            msg.serialize(buffer, msg.getSerializedSize());
            socket.send(buffer, msg.getSerializedSize());
        }
    } catch (const std::exception &e) {
        std::cerr << "Worms::Game::outputWorker:" << e.what() << std::endl;
        this->quit = true;
    }

    delete buffer;
}

void Worms::Game::start() {
    try {
        /* game loop */
        Utils::Chronometer chronometer;
        float lag = 0.0f;
        float32 timeStep = 1.0f / 60.0f;

        while (!quit) {
            double dt = chronometer.elapsed();
            lag += dt;

            this->currentTurnElapsed += dt;
            if (this->players[this->currentWorm].getBullets().size() > 0 &&
                !this->currentPlayerShot) {
                this->currentPlayerTurnTime = this->maxTurnTime;
                this->currentTurnElapsed = 0.0f;
                this->shotOnCourse = true;
                this->currentPlayerShot = true;
            }
            if (this->currentTurnElapsed >= this->currentPlayerTurnTime) {
                if (!this->shotOnCourse && this->drowningWormsQuantity == 0) {
                    if (this->players[this->currentWorm].getStateId() != Worm::StateID::Dead) {
                        this->players[this->currentWorm].setState(Worm::StateID::Still);
                    }
                    this->currentTurnElapsed = 0;
                    this->currentPlayerShot = false;

                    this->teams.endTurn(this->players);
                    this->currentTeam = this->teams.getCurrentTeam();
                    this->currentWorm = this->teams.getCurrentPlayerID();
                    this->currentWormToFollow = this->currentWorm;

                    this->processingClientInputs = true;
                    this->currentPlayerTurnTime = this->stage.turnTime;
                } else {
                    this->processingClientInputs = false;
                    //                    this->players[this->currentWorm].setState(Worm::StateID::Still);
                }
            }

            IO::PlayerMsg pMsg;
            if (this->inputs.at(this->currentTeam).pop(pMsg, false)) {
                if (this->processingClientInputs) {
                    if (this->currentPlayerShot) {
                        if (pMsg.input != IO::PlayerInput::startShot &&
                            pMsg.input != IO::PlayerInput::endShot) {
                            this->players.at(this->currentWorm).handleState(pMsg.input);
                        }
                    } else {
                        this->players.at(this->currentWorm).handleState(pMsg.input);
                    }
                }
            }

            /* updates the actors */
            for (auto &worm : this->players) {
                worm.update(dt);
            }

            /* updates the physics engine */
            for (int i = 0; i < 5 && lag > timeStep; i++) {
                this->physics.update(timeStep);
                lag -= timeStep;
            }

            if (this->players.at(this->currentWorm).getBullets().size() == 0) {
                if (!this->impactOnCourse) {
                    this->shotOnCourse = false;
                }
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

            /* serializes and updates the game state */
            this->snapshot.set(this->serialize());
            this->snapshot.swap();

            usleep(16 * 1000);
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl << "In Worms::Game::start" << std::endl;
    } catch (...) {
        std::cerr << "Unkown error in Worms::Game::start()" << std::endl;
    }
}

IO::GameStateMsg Worms::Game::serialize() const {
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

    m.bulletsQuantity = this->players[this->currentWorm].getBullets().size();
    uint8_t i = 0, j = 0;
    for (auto &bullet : this->players[this->currentWorm].getBullets()) {
        Math::Point<float> p = bullet.getPosition();
        m.bullets[i++] = p.x;
        m.bullets[i++] = p.y;
        m.bulletsAngle[j] = bullet.getAngle();
        m.bulletType[j++] = bullet.getWeaponID();
    }

    m.processingInputs = this->processingClientInputs;

    return m;
}

void Worms::Game::exit() {
    this->quit = true;
}

void Worms::Game::onNotify(const Worms::PhysicsEntity &entity, Event event) {
    switch (event) {
        /**
         * Because i didnt want to move all responsability of the bullets to
         * the game (until the refactor of the start), i added this function
         * that delegates to the player the responsability to iterate all over
         * the bullets and add the game as an observer
         */
        case Event::Shot: {
            this->players[this->currentWorm].addObserverToBullets(this);
            break;
        }
        /**
         * On explode, the game must check worms health.
         */
        case Event::Explode: {
            this->calculateDamage(dynamic_cast<const Bullet &>(entity));
            break;
        }
        /**
         * onExplode will create new Bullets in player's container, and we
         * need to listen to them.
         */
        case Event::OnExplode: {
            auto &bullet = dynamic_cast<const Bullet &>(entity);
            this->calculateDamage(bullet);
            this->players[this->currentWorm].onExplode(bullet, this->physics);
            this->players[this->currentWorm].addObserverToBullets(this);
            break;
        }
        case Event::Drowning: {
            this->drowningWormsQuantity++;
            break;
        }
        case Event::Drowned: {
            this->drowningWormsQuantity--;
            break;
        }
    }
}

void Worms::Game::calculateDamage(const Worms::Bullet &bullet) {
    ::Game::Bullet::DamageInfo damageInfo = bullet.getDamageInfo();
    for (auto &worm : this->players) {
        worm.acknowledgeDamage(damageInfo, bullet.getPosition());
        if (worm.getStateId() == Worm::StateID::Hit) {
            this->impactOnCourse = true;
        }
    }
    this->players[this->currentWorm].cleanBullets();
}
