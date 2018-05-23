/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <Box2D/Box2D.h>
#include <zconf.h>
#include <atomic>
#include <chrono>
#include <iostream>

#include "Game.h"
#include "Player.h"
#include "Stage.h"

Worms::Game::Game(const Stage &&stage) : physics(b2Vec2{0.0f, -10.0f}), stage(std::move(stage)) {
    int i{0};
    for (auto &wormPos : this->stage.getWormPositions()) {
        /* the first worm is the active player */
        this->players.emplace_back(this->physics, i == 0);
        this->players[i].setPosition(wormPos);
        i++;
    }

    /* sets the girders */
    for (auto &girder : this->stage.getGirderPositions()) {
        // a static body
        b2PolygonShape poly;

        b2BodyDef bdef;
        bdef.type = b2_staticBody;
        bdef.position.Set(0.0f, 0.0f);
        b2Body *staticBody = this->physics.createBody(bdef);

        b2FixtureDef fixture;
        fixture.density = 1;
        fixture.shape = &poly;

        const float height = 1.33f;
        const float width = 9.33;

        poly.SetAsBox(width / 2, height / 2, b2Vec2(girder.x, girder.y), 0);  // ground
        staticBody->CreateFixture(&fixture);
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

            IO::PlayerInput pi;
            if (playerStream->pop(pi, false)) {
                this->players[0].handleState(pi);
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

            /* sends the current game state */
            this->serialize(*output);

            prev = current;
            usleep(20 * 1000);
        }

        output->close();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl << "In Worms::Game::start" << std::endl;
        ;
    } catch (...) {
        std::cerr << "Unkown error in Worms::Game::start()" << std::endl;
    }
}

void Worms::Game::serialize(IO::Stream<IO::GameStateMsg> &s) const {
    assert(this->players.size() <= 20);

    const float w = this->stage.getWidth();

    IO::GameStateMsg m;
    m.num_worms = 0;
    for (const auto &worm : this->players) {
        m.positions[m.num_worms * 2] = worm.getPosition().x + (w / 2.0f);
        m.positions[m.num_worms * 2 + 1] = worm.getPosition().y;
        // TODO esto da ASCO. Cambiarlo cuando se pueda
        m.stateIDs[(int)m.num_worms] = worm.getStateId();
        if (worm.isActive()){
            m.activePlayerAngle = worm.getAngle();
        }
        m.num_worms++;
    }

    s << m;
}

void Worms::Game::exit() {
    this->quit = true;
}
