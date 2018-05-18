/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __Physics_H__
#define __Physics_H__

#include <Box2D/Box2D.h>

namespace Worms {

class Physics {
   public:
    Physics(b2Vec2 gravity);
    ~Physics() = default;
    void update(float dt);
    b2Body *createBody(b2BodyDef &bodyDef);

   private:
    b2Vec2 gravity;
    b2World world;
    int32 vIterations{6};
    int32 pIterations{2};
};
}

#endif  //__Physics_H__
