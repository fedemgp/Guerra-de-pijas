/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#ifndef __DynamicEntity_H__
#define __DynamicEntity_H__

namespace Worms{
    enum EntityID{EtWorm, EtBullet};
class Entity{
public:
    explicit Entity(EntityID id);
    virtual EntityID getEntityId();

private:
    EntityID id;
};
}


#endif //__DynamicEntity_H__
