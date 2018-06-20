/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#ifndef PHYSICS_ENTITY_H_
#define PHYSICS_ENTITY_H_

#include "Box2D/Box2D.h"

#include "Subject.h"

namespace Worms {
enum EntityID { EtWorm, EtBullet, Sensor, EtGirder };
class PhysicsEntity : public Subject {
   public:
    explicit PhysicsEntity(EntityID id);
    PhysicsEntity(PhysicsEntity &&other);
    PhysicsEntity(PhysicsEntity &copy) = delete;

    virtual EntityID getEntityId();
    virtual void startContact(Worms::PhysicsEntity *physicsEntity) {}
    virtual void startContact(Worms::PhysicsEntity *physicsEntity, b2Contact &contact) {}
    virtual void endContact(Worms::PhysicsEntity *physicsEntity) {}
    virtual void endContact(Worms::PhysicsEntity *physicsEntity, b2Contact &contact) {}
    virtual void contactWith(PhysicsEntity &physicsEntity, b2Contact &contact) {}

   private:
    EntityID id;
    bool handlingContact{false};
};
}  // namespace Worms

#endif
