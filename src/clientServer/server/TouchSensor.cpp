#include "TouchSensor.h"
#include <iostream>

/**
 * @brief Construct a TouchSensor for the given body and shape.
 *
 * @param body Body that the touch sensor belongs to.
 * @param shape Sensor shape.
 * @param contactCount The initial contact count in case it's attached to a body.
 */
Worms::TouchSensor::TouchSensor(b2Body &body, b2PolygonShape &shape, int contactCount)
    : PhysicsEntity(EntityID::Sensor), contactCount(contactCount) {
    /* fixture definition using the given shape */
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1;
    fixtureDef.isSensor = true;

    this->fixture = body.CreateFixture(&fixtureDef);
    this->fixture->SetUserData(this);
}

/**
 * @brief Called whenever the sensor started contacting another entity.
 *
 * @param Contacted entity.
 */
void Worms::TouchSensor::startContact(PhysicsEntity *physicsEntity) {
    this->contactCount++;
}

/**
 * @brief Called whenever the sensor stopped contacting another entity.
 *
 * @param Entity.
 */
void Worms::TouchSensor::endContact(PhysicsEntity *physicsEntity) {
    this->contactCount--;
}

/**
 * @brief Whether the sensor is active or not (i.e. touching another body).
 *
 * @return true is active.
 */
bool Worms::TouchSensor::isActive() const {
    return (this->contactCount > 0);
}
