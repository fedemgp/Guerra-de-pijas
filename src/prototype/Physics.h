#ifndef PHYSICS_H
#define PHYSICS_H

#include "Box2D/Box2D.h"

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

}

#endif //PHYSICS_H
