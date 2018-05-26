/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#include "Bullet.h"
Worms::Bullet::Bullet(Math::Point<float> p, Worms::Physics &physics): Entity(Worms::EntityID::EtBullet),
                                                                      physics(physics){
    this->bodyDef.type = b2_dynamicBody;
    this->bodyDef.position.Set(p.x, p.y);
    this->bodyDef.fixedRotation = true;

    this->body = this->physics.createBody(this->bodyDef);
    this->shape.m_p.Set(0.0f, 0.0f);
    this->shape.m_radius = 0.5f;
    this->fixture.shape = &this->shape;
    this->fixture.density = 1.0f;
    this->fixture.restitution = 0.1f;
    this->fixture.friction = 0.0f;

    this->body->CreateFixture(&this->fixture);
    this->body->SetUserData(this);
}

void Worms::Bullet::update(float dt){
    if (!this->impulseApplied){
        float32 mass = this->body->GetMass();
        b2Vec2 impulses = {mass * 5.0f, mass * 5.0f};
        this->body->ApplyLinearImpulseToCenter(impulses, true);
        this->impulseApplied = true;
    }
}

Math::Point<float> Worms::Bullet::getPosition() const{
    b2Vec2 p = this->body->GetPosition();
    return Math::Point<float>(p.x, p.y);
}

