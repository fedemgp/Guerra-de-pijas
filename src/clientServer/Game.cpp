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
#include "World.h"

Worms::Game::Game(const World &&level) : physics(b2Vec2{0.0f, -10.0f}), level(std::move(level)) {
    for (auto &wormPos : this->level.getWormPosition()) {
        Player p{this->physics};
        p.setPosition(wormPos);
        this->players.emplace_back(p);
    }

    // a static body
    b2PolygonShape poly;

    b2BodyDef bdef;
    bdef.type = b2_staticBody;
    bdef.position.Set(0.0f, 0.0f);
    b2Body *staticBody = this->physics.createBody(bdef);

    b2FixtureDef fixture;
    fixture.density = 1;
    fixture.shape = &poly;

    // add four walls to the static body
    const float height = level.getHeight();
    const float width = level.getWidth();

    poly.SetAsBox(width / 2.0f, 1, b2Vec2(0, 0), 0);  // ground
    staticBody->CreateFixture(&fixture);
    poly.SetAsBox(width / 2.0f, 1, b2Vec2(0, height), 0);  // ceiling
    staticBody->CreateFixture(&fixture);
    poly.SetAsBox(1, height / 2.0f, b2Vec2(width / -2.0f, height / 2.0f), 0);  // left wall
    staticBody->CreateFixture(&fixture);
    poly.SetAsBox(1, height / 2.0f, b2Vec2(width / 2.0f, height / 2.0f), 0);  // right wall
    staticBody->CreateFixture(&fixture);
}

void Worms::Game::start(IO::Stream<IO::GameStateMsg> *output,
                        IO::Stream<IO::PlayerInput> *playerStream) {

    try {

        /* game loop */
        std::chrono::high_resolution_clock::time_point prev = std::chrono::high_resolution_clock::now();
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
    } catch (std::exception &e){
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unkown error in Worms::Game::start()" << std::endl;
    }
}

void Worms::Game::serialize(IO::Stream<IO::GameStateMsg> &s) const {
    assert(this->players.size() <= 20);

    const float w = this->level.getWidth();
    const float h = this->level.getHeight();

    IO::GameStateMsg m;
    m.num_worms = 0;
    for (const auto &worm : this->players) {
        m.positions[m.num_worms * 2] = (worm.getPosition().x + w / 2.0f) / w;
        m.positions[m.num_worms * 2 + 1] = worm.getPosition().y / h;
        m.num_worms++;
    }

    s << m;
}

void Worms::Game::exit() {
    this->quit = true;
}