#ifndef TOUCH_SENSOR_H_
#define TOUCH_SENSOR_H_

#include "Physics.h"
#include "PhysicsEntity.h"

namespace Worms {
class TouchSensor : public PhysicsEntity {
   public:
    TouchSensor(b2Body &body, b2PolygonShape &shape, int contactCount);
    ~TouchSensor() = default;

    bool isActive() const;

    virtual void startContact(PhysicsEntity *physicsEntity);
    virtual void endContact(PhysicsEntity *physicsEntity);

   private:
    int contactCount{0};
    b2Fixture *fixture{nullptr};
};
}  // namespace Worms

#endif
