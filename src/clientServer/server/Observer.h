/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 06/06/18
 */

#ifndef __OBSERVER_H__
#define __OBSERVER_H__

enum class Event { Explode, OnExplode, Shot };

namespace Worms {
class PhysicsEntity;
}  // namespace Worms

class Observer {
   public:
    virtual ~Observer() = default;
    virtual void onNotify(const Worms::PhysicsEntity &entity, Event event) = 0;
};

#endif  //__OBSERVER_H__
