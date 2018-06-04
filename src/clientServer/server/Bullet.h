/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#ifndef __BULLET_H__
#define __BULLET_H__

#include "Physics.h"
#include "PhysicsEntity.h"
#include "Point.h"

#define PI 3.14159265

namespace Worms {
struct DamageInfo {
    uint16_t damage;
    float radius;
};
struct BulletInfo {
    DamageInfo dmgInfo;
    float angle;
    uint16_t power;
    Math::Point<float> point;
    float safeNonContactDistance;
    float restitution;
    float friction;
};
/**
 * forward declaration of weapon.
 */
class Weapon;
class Bullet : public PhysicsEntity {
   public:
    Bullet(BulletInfo i, Worms::Physics &physics);
    Bullet(BulletInfo i, Worms::Physics &physics, uint16_t timeout);
    ~Bullet();
    void update(float dt, Weapon &w);
    Math::Point<float> getPosition() const;
    float getAngle() const;
    virtual void startContact() override;
    virtual void endContact() override;
    bool hasExploded();
    DamageInfo getDamageInfo();

   private:
    b2Body *body{nullptr};
    b2BodyDef bodyDef;
    b2CircleShape shape;
    b2FixtureDef fixture;
    Worms::Physics &physics;
    float angle{0};
    bool impulseApplied{false};
    float radius{0.5f};
    uint16_t timeout{0};
    float timeElapsed{0.0f};
    uint16_t power{0};
    DamageInfo damageInfo;
    bool madeImpact{false};
};
}  // namespace Worms

#endif  //__BULLET_H__
