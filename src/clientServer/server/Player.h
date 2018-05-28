/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#define MIN_ANGLE -90
#define MAX_ANGLE 84.375f
#define ANGLE_STEP 5.625f

#define PLAYER_WIDTH 0.8f

#define PLAYER_HEIGHT 2.0f

#include "Bullet.h"
#include "GameStateMsg.h"
#include "Physics.h"
#include "PlayerState.h"
#include "Point.h"
#include "Stream.h"

enum class PlayerState { movingRight, movingLeft, still };

namespace Worms {
enum class Direction { right, left, up, down };

class Player : public PhysicsEntity {
   public:
    Direction direction;
    uint16_t health{0};

    explicit Player(Physics &physics);
    ~Player() = default;

    void update(float dt);
    float getAngle() const;
    void serialize(IO::Stream<IO::GameStateMsg> &s) const {}
    void setPosition(const Math::Point<float> &newPos);
    Math::Point<float> getPosition() const;
    void handleState(IO::PlayerInput pi);
    Worm::StateID getStateId() const;
    void setState(Worm::StateID stateID);
    void increaseAngle();
    void decreaseAngle();
    int getContactCount();
    virtual void startContact() override;
    virtual void endContact() override;
    void shoot(int shotPower);
    std::shared_ptr<Worms::Bullet> getBullet() const;

   private:
    std::shared_ptr<Worms::State> state{nullptr};
    b2Body *body{nullptr};
    b2BodyDef bodyDef;
    b2PolygonShape shape;
    b2FixtureDef fixture;
    Physics &physics;
    std::shared_ptr<Worms::Bullet> bullet{nullptr};
    float angle{0};
    int numContacts{0};
};
}  // namespace Worms

#endif  //__PLAYER_H__
