/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#ifndef __BULLET_H__
#define __BULLET_H__

#include <GameStateMsg.h>
#include "../Config/Config.h"
#include "Observer.h"
#include "../Physics.h"
#include "../PhysicsEntity.h"
#include "Point.h"

namespace Worms {
struct BulletInfo {
    Game::Bullet::DamageInfo dmgInfo;
    Math::Point<float> point;
    float angle;
    float power;
    float safeNonContactDistance;
    float restitution;
    float friction;
    uint8_t explotionTimeout;
    Event explodeEvent;
    float radius;
    float dampingRatio;
    bool windAffected;
};
/**
 * forward declaration of weapon.
 */
class Weapon;
class Bullet : public PhysicsEntity {
   public:
    Bullet(BulletInfo &i, Worms::Physics &physics, Worm::WeaponID weaponID);
    ~Bullet();
    /**
     * Apply initial impulse in the first iteration, or estimate the
     * bullet's tangential velocity to guide the animation. Finally, checks if
     * an Explode event ocurred, and notify his observer if so.
     * @param dt
     * @param w
     */
    void update(float dt, Worms::Wind wind);
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
    ::Game::Bullet::DamageInfo getDamageInfo() const;
    bool operator<(Worms::Bullet &other);
    Worm::WeaponID getWeaponID() const;

   private:
    b2Body *body{nullptr};
    b2BodyDef bodyDef;
    b2CircleShape shape;
    b2FixtureDef fixture;
    Worms::Physics &physics;
    bool impulseApplied{false};
    float timeElapsed{0.0f};
    bool madeImpact{false};
    Worm::WeaponID weaponID;
    BulletInfo info;
    bool keepUpdating{true};
    Math::Point<float> lastPosition{0, 0};

    void destroyBody();
};
}  // namespace Worms

#endif  //__BULLET_H__
