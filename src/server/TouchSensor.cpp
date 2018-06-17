#include "TouchSensor.h"
#include <iostream>

/**
 * @brief Construct a TouchSensor for the given body and shape.
 *
 * @param body Body that the touch sensor belongs to.
 * @param shape Sensor shape.
 */
Worms::TouchSensor::TouchSensor(b2Body &body, b2Shape &shape) : PhysicsEntity(EntityID::Sensor) {
    /* fixture definition using the given shape */
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1;
    fixtureDef.isSensor = true;

    this->fixture = body.CreateFixture(&fixtureDef);
    this->fixture->SetUserData(this);
}

Worms::TouchSensor::iterator Worms::TouchSensor::begin() {
    return this->contacts.begin();
}

Worms::TouchSensor::iterator Worms::TouchSensor::end() {
    return this->contacts.end();
}

/**
 * @brief Called whenever the sensor started contacting another entity.
 *
 * @param Contacted entity.
 */
void Worms::TouchSensor::startContact(PhysicsEntity *physicsEntity, b2Contact &contact) {
    /* checks if the entity is in the ignore list */
    if (!this->isIgnored(physicsEntity)) {
        b2Manifold manifold;
        const b2Transform t1 = contact.GetFixtureA()->GetBody()->GetTransform();
        const b2Transform t2 = contact.GetFixtureB()->GetBody()->GetTransform();

        contact.Evaluate(&manifold, t1, t2);

        if (contact.GetFixtureA()->GetUserData() == physicsEntity) {
            this->contacts[physicsEntity] = -manifold.localNormal;
        } else {
            this->contacts[physicsEntity] = manifold.localNormal;
        }
    }
}

/**
 * @brief Called whenever the sensor stopped contacting another entity.
 *
 * @param Entity.
 */
void Worms::TouchSensor::endContact(PhysicsEntity *physicsEntity, b2Contact &contact) {
    /* checks if the entity is in the ignore list */
    if (!this->isIgnored(physicsEntity)) {
        this->contacts.erase(physicsEntity);
    }
}

/**
 * @brief Whether the sensor is active or not (i.e. touching another body).
 *
 * @return true is active.
 */
bool Worms::TouchSensor::isActive() const {
    return (this->contacts.size() > 0);
}

/**
 * @brief Adds an entity that should be ignored by the sensor.
 *
 * @param other Entity to ignore.
 */
void Worms::TouchSensor::ignore(PhysicsEntity &other) {
    this->ignoredEntities.push_back(&other);
}

/**
 * @brief Checks if a given entity is in the ignore list.
 *
 * @param entity Entity to check.
 * @return true if the given entity is ignored by this sensor.
 */
bool Worms::TouchSensor::isIgnored(PhysicsEntity *entity) {
    return std::find(this->ignoredEntities.begin(), this->ignoredEntities.end(), entity) !=
           this->ignoredEntities.end();
}
