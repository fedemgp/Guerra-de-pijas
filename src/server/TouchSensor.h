#ifndef TOUCH_SENSOR_H_
#define TOUCH_SENSOR_H_

#include <unordered_map>
#include "Physics.h"
#include "PhysicsEntity.h"

namespace Worms {
class TouchSensor : public PhysicsEntity {
   public:
    using iterator = std::unordered_map<PhysicsEntity *, b2Vec2>::iterator;

    TouchSensor(b2Body &body, b2Shape &shape);
    ~TouchSensor() = default;

    iterator begin();
    iterator end();

    bool isActive() const;
    void ignore(PhysicsEntity &other);

    void startContact(PhysicsEntity *physicsEntity, b2Contact &contact);
    void endContact(PhysicsEntity *physicsEntity, b2Contact &contact);

   private:
    bool isIgnored(PhysicsEntity *entity);

    b2Fixture *fixture{nullptr};
    std::vector<PhysicsEntity *> ignoredEntities;
    std::unordered_map<PhysicsEntity *, b2Vec2> contacts;
    std::unordered_map<PhysicsEntity *, b2Fixture *> contactFixtures;
};
}  // namespace Worms

#endif
