#include "Girder.h"

Worms::Girder::Girder(const Worms::GirderData &data, Worms::Physics &physics)
    : PhysicsEntity(EntityID::EtGirder), angle(data.angle) {
    b2PolygonShape poly;

    b2BodyDef bdef;
    bdef.type = b2_staticBody;
    bdef.position.Set(0.0f, 0.0f);
    b2Body *staticBody = physics.createBody(bdef);

    b2FixtureDef fixture;
    fixture.density = 1;
    fixture.shape = &poly;

    poly.SetAsBox(data.length / 2, data.height / 2, b2Vec2(data.pos.x, data.pos.y),
                  data.angle * (PI / 180.0f));
    staticBody->CreateFixture(&fixture);

    staticBody->SetUserData(this);
}

Worms::Girder::Girder(Worms::Girder &&other) noexcept :
        PhysicsEntity(other.id), angle(other.angle){
    this->handlingContact = other.handlingContact;
    this->numObservers = other.numObservers;
    this->observers = std::move(other.observers);
}
