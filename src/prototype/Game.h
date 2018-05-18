#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL_timer.h>
#include "Player.h"
#include "World.h"

namespace Worms {

    class Game {
    public:
        std::atomic<bool> quit{false};

        Game(const World &&level) : physics(b2Vec2{0.0f, -10.0f}), level(std::move(level)) {
            for (auto &worm_pos : this->level.get_worm_positions()) {
                Player p{this->physics};
                p.set_position(worm_pos);
                this->players.emplace_back(p);
            }

            // a static body
            b2PolygonShape poly;

            b2BodyDef bdef;
            bdef.type = b2_staticBody;
            bdef.position.Set(0.0f, 0.0f);
            b2Body *staticBody = this->physics.create_body(bdef);

            b2FixtureDef fixture;
            fixture.density = 1;
            fixture.shape = &poly;

            // add four walls to the static body
            const float height = level.get_height();
            const float width = level.get_width();

            poly.SetAsBox(width / 2.0f, 1, b2Vec2(0, 0), 0);  // ground
            staticBody->CreateFixture(&fixture);
            poly.SetAsBox(width / 2.0f, 1, b2Vec2(0, height), 0);  // ceiling
            staticBody->CreateFixture(&fixture);
            poly.SetAsBox(1, height / 2.0f, b2Vec2(width / -2.0f, height / 2.0f), 0);  // left wall
            staticBody->CreateFixture(&fixture);
            poly.SetAsBox(1, height / 2.0f, b2Vec2(width / 2.0f, height / 2.0f), 0);  // right wall
            staticBody->CreateFixture(&fixture);
        }
        ~Game() {}

        void start(IO::Stream<IO::GameStateMsg> *output, IO::Stream<IO::PlayerInput> *player_stream) {
            /* game loop */
            uint32_t prev = SDL_GetTicks();  // TODO: don't use SDL, use something with more precision
            float lag = 0.0f;
            float32 time_step = 1.0f / 60.0f;

            while (!quit) {
                uint32_t current = SDL_GetTicks();
                float dt = static_cast<float>(current - prev) / 1000.0f;
                lag += dt;

                IO::PlayerInput pi;
                if (player_stream->pop(pi, false)) {
                    switch (pi) {
                        case IO::PlayerInput::move_left:
                            this->players[0].move_left();
                            break;
                        case IO::PlayerInput::move_right:
                            this->players[0].move_right();
                            break;
                        case IO::PlayerInput::stop_move:
                            this->players[0].stop_move();
                            break;
                    }
                }

                /* updates the actors */
                for (auto &worm : this->players) {
                    worm.update(dt);
                }

                /* updates the physics engine */
                for (int i = 0; i < 5 && lag > time_step; i++) {
                    this->physics.update(time_step);
                    lag -= time_step;
                }

                /* sends the current game state */
                this->serialize(*output);

                prev = current;
                usleep(20 * 1000);
            }

            output->close();
        }

        void serialize(IO::Stream<IO::GameStateMsg> &s) const {
            assert(this->players.size() <= 20);

            const float w = this->level.get_width();
            const float h = this->level.get_height();

            IO::GameStateMsg m;
            m.num_worms = 0;
            for (const auto &worm : this->players) {
                m.positions[m.num_worms * 2] = (worm.get_position().x + w / 2.0f) / w;
                m.positions[m.num_worms * 2 + 1] = worm.get_position().y / h;
                m.num_worms++;
            }

            s << m;
        }

        void exit(){
            this->quit = true;
        }

    private:
        Physics physics;
        World level;
        std::vector<Player> players;
    };
}  // namespace Worms

#endif //GAME_H
