#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <atomic>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>
#include "Box2D/Box2D.h"
#include "Exception.h"
#include "gui.h"

static std::atomic<bool> quit{false};

namespace Math {
    template <typename Numeric>
    class Point {
    public:
        Point(Numeric x, Numeric y) : x(x), y(y) {}
        ~Point() {}

        Point<Numeric> &operator=(const Point<Numeric> &other) {
            this->x = other.x;
            this->y = other.y;
            return *this;
        }

        Numeric x, y;
    };
}  // namespace Math

namespace Worms {

    class Physics {
    public:
        Physics(b2Vec2 gravity) : gravity(gravity), world(this->gravity) {}
        ~Physics() {}

        void update(float dt) {
            float32 v_iterations = 6.0f;
            float32 p_iterations = 2.0f;
            this->world.Step(dt, v_iterations, p_iterations);
        }

        b2Body *create_body(b2BodyDef &body_def) {
            return this->world.CreateBody(&body_def);
        }

    private:
        b2Vec2 gravity;
        b2World world;
    };

    enum class PlayerState { moving_right, moving_left, still };

    class Player {
    public:
        Player(Physics &physics) {
            this->body_def.type = b2_dynamicBody;
            this->body_def.position.Set(0.0f, 0.0f);

            this->body = physics.create_body(this->body_def);

            this->shape.SetAsBox(1.0f, 2.0f);
            this->fixture.shape = &this->shape;
            this->fixture.density = 1.0f;
            this->fixture.restitution = 0.3f;
            this->fixture.friction = 0.0f;

            this->body->CreateFixture(&this->fixture);
        }
        ~Player() {}

        void update(float dt) {
            float final_vel = 0.0f;
            switch (this->state) {
                case PlayerState::still:
                    final_vel = 0.0f;
                    break;
                case PlayerState::moving_left:
                    final_vel = -3.0f;
                    break;
                case PlayerState::moving_right:
                    final_vel = 3.0f;
                    break;
            }

            b2Vec2 vel = this->body->GetLinearVelocity();
            const float delta = final_vel - vel.x;
            float impulse = this->body->GetMass() * delta;
            this->body->ApplyLinearImpulse(b2Vec2(impulse, 0), this->body->GetWorldCenter(), true);
        }

        void serialize(IO::Stream<IO::GameStateMsg> &s) const {}

        void set_position(const Math::Point<float> &new_pos) {
            this->body->SetTransform(b2Vec2(new_pos.x, new_pos.y), body->GetAngle());
        }

        Math::Point<float> get_position() const {
            const b2Vec2 &pos = this->body->GetPosition();
            return Math::Point<float>{pos.x, pos.y};
        }

        void move_right() {
            this->state = PlayerState::moving_right;
        }

        void move_left() {
            this->state = PlayerState::moving_left;
        }

        void stop_move() {
            this->state = PlayerState::still;
        }

    private:
        b2Body *body;
        b2BodyDef body_def;
        b2PolygonShape shape;
        b2FixtureDef fixture;
        PlayerState state{PlayerState::still};
    };

    class World {
    public:
        World() {
            this->player_positions.emplace_back(Math::Point<float>{0.0f, 15.0f});
        }
        ~World() {}

        const std::vector<Math::Point<float>> &get_worm_positions() const {
            return this->player_positions;
        }

        float get_height() const {
            return this->height;
        }

        float get_width() const {
            return this->width;
        }

    private:
        std::vector<Math::Point<float>> player_positions;
        float width{30.0f}, height{30.0f};
    };

    class Game {
    public:
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

    private:
        Physics physics;
        World level;
        std::vector<Player> players;
    };
}  // namespace Worms

void _exit_handler(int s) {
    quit = true;
}

int main() {
    try {
        signal(SIGINT, _exit_handler);
        signal(SIGTERM, _exit_handler);

        IO::Stream<IO::GameStateMsg> server_stream;
        IO::Stream<IO::PlayerInput> player_stream;

        GUI::Window window{};
        window.clear();

        Worms::Game game{Worms::World{}};
        std::thread game_thread =
                std::thread(std::bind(&Worms::Game::start, &game, &server_stream, &player_stream));

        GUI::Game gui_game{window};
        std::thread gui_thread =
                std::thread(std::bind(&GUI::Game::start, &gui_game, &server_stream, &player_stream));

        game_thread.join();

        quit = true;
        gui_thread.join();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}