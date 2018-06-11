/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <Box2D/Box2D.h>
#include <zconf.h>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
//#include <random>

#include "Config.h"
#include "Game.h"
#include "Player.h"
#include "Stage.h"
#include "ImpactOnCourse.h"

Worms::Game::Game(Stage &&stage)
    : physics(b2Vec2{0.0f, -10.0f}),
      stage(std::move(stage)),
      maxTurnTime(::Game::Config::getInstance().getExtraTurnTime()),
      gameTurn(*this) {
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

    this->teams.makeTeams(this->players, this->stage.getNumTeams());

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

    this->gameClock.addObserver(this);
}

void Worms::Game::start(IO::Stream<IO::GameStateMsg> *output,
                        IO::Stream<IO::PlayerMsg> *playerStream) {
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

            this->gameClock.update(dt);
            this->gameTurn.update(dt);

            IO::PlayerMsg pMsg;
            if (playerStream->pop(pMsg, false)) {
                if (this->processingClientInputs) {
                    if (this->currentPlayerShot) {
                        if (pMsg.input != IO::PlayerInput::startShot && pMsg.input != IO::PlayerInput::endShot) {
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

            /* updates the physics engine */
            for (int i = 0; i < 5 && lag > timeStep; i++) {
                this->physics.update(timeStep);
                lag -= timeStep;
            }

//            if (this->players.at(this->currentWorm).getBullets().size() == 0){
//                if (!this->impactOnCourse){
//                    this->shotOnCourse = false;
//                }
//            }
//            if (this->impactOnCourse) {
//                this->impactOnCourse = false;
//                this->shotOnCourse = false;
//                for (size_t i = 0; i < this->players.size(); i++) {
//                    Worm::StateID wormState = this->players[i].getStateId();
//                    if (wormState != Worm::StateID::Still && wormState != Worm::StateID::Dead) {
//                        this->impactOnCourse = true;
//                        this->shotOnCourse = true;
//                        this->currentWormToFollow = i;
//                    }
//                }
//                if (!this->impactOnCourse) {
//                    for (auto &worm : this->players) {
//                        Worm::StateID wormState = worm.getStateId();
//                        if (worm.health == 0) {
//                            if (wormState != Worm::StateID::Die &&
//                                wormState != Worm::StateID::Dead) {
//                                worm.setState(Worm::StateID::Die);
//                            }
//                            if (wormState != Worm::StateID::Dead) {
//                                this->impactOnCourse = true;
//                                this->shotOnCourse = true;
//                            }
//                        }
//                    }
//                }
//            }

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

void Worms::Game::endTurn() {
//    if (!this->shotOnCourse && this->drowningWormsQuantity == 0) {
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
        this->gameClock.restart();
        this->gameTurn.restart();
//    } else {
//        this->processingClientInputs = false;
//        //                    this->players[this->currentWorm].setState(Worm::StateID::Still);
//    }
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
    m.elapsedTurnSeconds = this->gameClock.getTimeElapsed();
    m.currentPlayerTurnTime = this->gameClock.getTurnTime();
    m.currentWorm = this->currentWorm;
    m.currentWormToFollow = this->currentWormToFollow;
    m.currentTeam = this->currentTeam;
    m.activePlayerAngle = this->players[this->currentWorm].getWeaponAngle();
    m.activePlayerWeapon = this->players[this->currentWorm].getWeaponID();

    m.bulletsQuantity = this->players[this->currentWorm].getBullets().size();
    uint8_t i = 0, j = 0;
    for (auto &bullet : this->players[this->currentWorm].getBullets()){
        Math::Point<float> p = bullet.getPosition();
        m.bullets[i++] = p.x;
        m.bullets[i++] = p.y;
        m.bulletsAngle[j] = bullet.getAngle();
        m.bulletType[j++] = bullet.getWeaponID();
    }

    m.processingInputs = this->processingClientInputs;

    s << m;
}

void Worms::Game::exit() {
    this->quit = true;
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
             this->players[this->currentWorm].addObserverToBullets(this);
             this->gameClock.playerShot();
             this->gameTurn.playerShot(this->players[this->currentWorm].getWeaponID());
             this->shotOnCourse = true;
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
        /**
         * onExplode will create new Bullets in player's container, and we
         * need to listen to them.
         */
        case Event::OnExplode: {
            auto &bullet = dynamic_cast<const Bullet &>(subject);
            this->calculateDamage(bullet);
            this->players[this->currentWorm].onExplode(bullet, this->physics);
            this->players[this->currentWorm].addObserverToBullets(this);
            break;
        }
        case Event::Hit: {
            this->hitWormsQuantity++;
            this->impactOnCourse = true;
            this->gameTurn.wormHit(dynamic_cast<const Player &>(subject).getId());
            break;
        }
        case Event::EndHit: {
            this->hitWormsQuantity--;
            this->gameTurn.wormEndHit(dynamic_cast<const Player &>(subject).getId());
            break;
        }
        case Event::Drowning: {
            this->drowningWormsQuantity++;
            this->gameTurn.wormDrowning(dynamic_cast<const Player &>(subject).getId());
            break;
        }
        case Event::Drowned: {
            this->drowningWormsQuantity--;
            this->gameTurn.wormDrowned(dynamic_cast<const Player &>(subject).getId());
            break;
        }
        case Event::NewWormToFollow: {
            this->currentWormToFollow = dynamic_cast<const ImpactOnCourse &>(subject).getWormToFollow();
            break;
        }
        case Event::ImpactEnd: {
            auto &wormsHit = dynamic_cast<ImpactOnCourse &>(subject).getWormsHit();
            for (auto worm : wormsHit) {
                Worm::StateID wormState = this->players[worm].getStateId();
                if (this->players[worm].health == 0) {
                    if (wormState != Worm::StateID::Die &&
                        wormState != Worm::StateID::Dead) {
                        this->players[worm].setState(Worm::StateID::Die);
                    }
                    if (wormState != Worm::StateID::Dead) {
                        dynamic_cast<ImpactOnCourse &>(subject).impactNotEnded();
                    }
                }
            }
        }
        case Event::EndTurn: {
            this->processingClientInputs = false;
            this->gameTurn.endTurn();
            break;
        }
        case Event::TurnEnded: {
            this->endTurn();
            break;
        }
    }
}

void Worms::Game::calculateDamage(const Worms::Bullet &bullet){
    ::Game::Bullet::DamageInfo damageInfo = bullet.getDamageInfo();
    for (auto &worm : this->players) {
        worm.acknowledgeDamage(damageInfo, bullet.getPosition());
    }
    this->players[this->currentWorm].cleanBullets();
}
