#ifndef PLAYER_H
#define PLAYER_H

#include "Box2D/Box2D.h"
#include "Physics.h"
#include "Point.h"
#include "stream.h"

enum class PlayerState { moving_right, moving_left, still };

namespace Worms {

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

        void serialize(IO::Stream <IO::GameStateMsg> &s) const {}

        void set_position(const Math::Point<float> &new_pos) {
            this->body->SetTransform(b2Vec2(new_pos.x, new_pos.y), body->GetAngle());
        }

        Math::Point<float> get_position() const {
            const b2Vec2 &pos = this->body->GetPosition();
            return Math::Point < float > {pos.x, pos.y};
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

}

#endif // PLAYER_H
