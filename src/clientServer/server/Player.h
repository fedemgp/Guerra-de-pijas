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

    void update(float dt);
    void serialize(IO::Stream<IO::GameStateMsg> &s) const {}
    void setPosition(const Math::Point<float> &newPos);
    Math::Point<float> getPosition() const;
    void handleState(IO::PlayerInput pi);
    Worm::StateID getStateId() const;
    void setState(Worm::StateID stateID);
    int getContactCount();
    int getWormContactCount();
    void startContact(Worms::PhysicsEntity *physicsEntity) override;
    void endContact(Worms::PhysicsEntity *physicsEntity) override;
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
    void setTeam(uint8_t team);
    void increaseHealth(float percentage);
    uint8_t getTeam() const;
    void setId(uint8_t id);
    uint8_t getId() const;
    void setWeaponTimeout(uint8_t time);

   private:
    std::shared_ptr<Worms::State> state{nullptr};
    std::shared_ptr<Worms::Weapon> weapon{nullptr};
    b2Body *body{nullptr};
    b2BodyDef bodyDef;
    b2PolygonShape shape;
    b2FixtureDef fixture;
    Physics &physics;
    const int waterLevel;
    int numContacts{0};
    uint8_t team;
    uint8_t id;
    int numWormContacts{0};
    int numBulletContacs{0};
};
}  // namespace Worms

#endif  //__PLAYER_H__
