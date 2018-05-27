/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#ifndef __DynamicEntity_H__
#define __DynamicEntity_H__

namespace Worms {
enum EntityID { EtWorm, EtBullet };
class PhysicsEntity {
   public:
    explicit PhysicsEntity(EntityID id);
    virtual EntityID getEntityId();
    virtual void startContact() = 0;
    virtual void endContact() = 0;

   private:
    EntityID id;
};
}

#endif  //__DynamicEntity_H__
