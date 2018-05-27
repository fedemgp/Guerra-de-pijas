/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#ifndef __BULLET_H__
#define __BULLET_H__

#include "Physics.h"
#include "Point.h"
#include "Entity.h"

#define PI 3.14159265

namespace Worms{
    class Bullet: public Entity{
    public:
        Bullet(Math::Point<float> p, float angle, Worms::Physics &physics);
        ~Bullet() = default;
        void update(float dt);
        Math::Point<float> getPosition() const;
        float getAngle() const;

    private:
        b2Body *body{nullptr};
        b2BodyDef bodyDef;
        b2CircleShape shape;
        b2FixtureDef fixture;
        Worms::Physics &physics;
        float angle{0};
        int numContacts{0};
        bool impulseApplied{false};
        float radius{0.5f};
        Math::Point<float> position{0.0f, 0.0f};
    };
}//namespace Worms


#endif //__BULLET_H__
