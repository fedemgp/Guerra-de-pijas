/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __Player_H__
#define __Player_H__

#include "GameStateMsg.h"
#include "Physics.h"
#include "Point.h"
#include "Stream.h"

enum class PlayerState { movingRight, movingLeft, still };

namespace Worms {

class Player {
   public:
    Player(Physics &physics);
    ~Player() = default;
    void update(float dt);
    void serialize(IO::Stream<IO::GameStateMsg> &s) const {}
    void setPosition(const Math::Point<float> &newPos);
    Math::Point<float> getPosition() const;
    void moveRight();
    void moveLeft();
    void stopMove();

   private:
    b2Body *body;
    b2BodyDef bodyDef;
    b2PolygonShape shape;
    b2FixtureDef fixture;
    PlayerState state{PlayerState::still};
};
}

#endif  //__Player_H__
