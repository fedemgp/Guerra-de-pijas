/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#define MIN_ANGLE -90
#define MAX_ANGLE 84.375f
#define ANGLE_STEP 5.625f

#include "GameStateMsg.h"
#include "Physics.h"
#include "PlayerState.h"
#include "Point.h"
#include "Stream.h"

enum class PlayerState { movingRight, movingLeft, still };

namespace Worms {
enum class Direction { right, left, up, down };

class Player {
   public:
    Direction direction;
    explicit Player(Physics &physics, bool active);
    ~Player() = default;
    void update(float dt);
    bool isActive() const;
    float getAngle() const;
    void serialize(IO::Stream<IO::GameStateMsg> &s) const {}
    void setPosition(const Math::Point<float> &newPos);
    Math::Point<float> getPosition() const;
    void handleState(IO::PlayerInput pi);
    Worm::StateID getStateId() const;
    void setState(Worm::StateID stateID);
    void increaseAngle();
    void decreaseAngle();
    void startContact();
    void endContact();

private:
    std::shared_ptr<Worms::State> state;
    b2Body *body;
    b2BodyDef bodyDef;
    b2PolygonShape shape;
    b2FixtureDef fixture;
    float angle{0};
    bool active{false};
};
}

#endif  //__PLAYER_H__
