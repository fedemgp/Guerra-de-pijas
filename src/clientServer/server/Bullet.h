/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#ifndef __BULLET_H__
#define __BULLET_H__

#include "Observer.h"
#include "Physics.h"
#include "PhysicsEntity.h"
#include "Point.h"

namespace Worms {
struct DamageInfo {
    uint16_t damage;
    float radius;
};
struct BulletInfo {
    DamageInfo dmgInfo;
    float angle;
    float power;
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
    Bullet(BulletInfo &i, Worms::Physics &physics);
    Bullet(BulletInfo &i, Worms::Physics &physics, uint16_t timeout);
    ~Bullet();
    /**
     * Apply initial impulse in the first iteration, or estimate the
     * bullet's tangential velocity to guide the animation. Finally, checks if
     * an Explode event ocurred, and notify his observer if so.
     * @param dt
     * @param w
     */
    void update(float dt, Weapon &w);
    Math::Point<float> getPosition() const;
    float getAngle() const;
    /**
     * Sets its impact boolean to true. Usefull for detecting explosion in
     * bullets that explode on first impact.
     * @param physicsEntity
     */
    virtual void startContact(Worms::PhysicsEntity *physicsEntity) override;
    virtual void endContact(Worms::PhysicsEntity *physicsEntity) override;
    /**
     * return true if the bullet is under the water, if its timeout (in the
     * case that it have it) has been reached, or if it has collided with
     * something
     * @return
     */
    bool hasExploded() const;
    DamageInfo getDamageInfo() const;

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
    float power{0};
    DamageInfo damageInfo;
    bool madeImpact{false};
};

struct ExplosionChecker {
    bool operator()(const Bullet &bullet) {
        return bullet.hasExploded();
    }
};
}  // namespace Worms

#endif  //__BULLET_H__
