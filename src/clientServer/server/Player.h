/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#define PLAYER_WIDTH 0.8f

#define PLAYER_HEIGHT 2.0f

#include "Bullet.h"
#include "GameStateMsg.h"
#include "Physics.h"
#include "PlayerState.h"
#include "Point.h"
#include "Stream.h"
#include "TouchSensor.h"
#include "Weapon.h"

enum class PlayerState { movingRight, movingLeft, still };

namespace Worms {
enum class Direction { right, left, up, down };

class Player : public PhysicsEntity {
   public:
    Direction direction;
    Direction lastWalkDirection;
    bool canWalk{true};
    float health{0};

    explicit Player(Physics &physics);
    ~Player() = default;

    /* contact handlers */
    virtual void contactWith(PhysicsEntity &other, b2Contact &contact);

    bool isOnGround() const;

    void update(float dt);
    void serialize(IO::Stream<IO::GameStateMsg> &s) const {}
    void setPosition(const Math::Point<float> &newPos);
    Math::Point<float> getPosition() const;
    void handleState(IO::PlayerInput pi);
    Worm::StateID getStateId() const;
    void setState(Worm::StateID stateID);
    float getWeaponAngle() const;
    const Worm::WeaponID &getWeaponID() const;
    void setWeapon(const Worm::WeaponID &id);
    void increaseWeaponAngle();
    void decreaseWeaponAngle();
    void startShot();
    void endShot();
    std::shared_ptr<Worms::Bullet> getBullet() const;
    void destroyBullet();
    void acknowledgeDamage(Worms::DamageInfo damageInfo, Math::Point<float> epicenter);
    void landDamage(float yDistance);
    void setTeam(uint8_t team);
    void increaseHealth(float percentage);
    uint8_t getTeam() const;
    void setId(uint8_t id);
    uint8_t getId() const;
    void setWeaponTimeout(uint8_t time);

    bool operator!=(const Player &other);
    bool operator==(const Player &other);

   private:
    b2Body *createBody(b2BodyType type);

    b2Body *body{nullptr};
    b2Body *body_kinematic{nullptr};
    TouchSensor *footSensor;

    std::shared_ptr<Worms::State> state{nullptr};
    std::shared_ptr<Worms::Weapon> weapon{nullptr};
    Physics &physics;
    const int waterLevel;
    uint8_t team;
    uint8_t id;
};
}  // namespace Worms

#endif  //__PLAYER_H__
