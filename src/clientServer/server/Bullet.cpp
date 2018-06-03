/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 26/05/18
 */

#include "Bullet.h"
#include "Config.h"
#include <cmath>
#include <iostream>

Worms::Bullet::Bullet(BulletInfo info, Worms::Physics &physics)
    : PhysicsEntity(Worms::EntityID::EtBullet), physics(physics) {
    float distance = info.safeNonContactDistance + this->radius;
    this->bodyDef.type = b2_dynamicBody;
    this->bodyDef.position.Set(info.point.x + distance * cos(info.angle * PI / 180.0f),
                               info.point.y + distance * sin(info.angle * PI / 180.0f));
    this->bodyDef.fixedRotation = true;

    this->body = this->physics.createBody(this->bodyDef);
    this->shape.m_p.Set(0.0f, 0.0f);
    this->shape.m_radius = this->radius;
    this->fixture.shape = &this->shape;
    this->fixture.density = 1.0f;
    this->fixture.restitution = 0.1f;
    this->fixture.friction = 0.0f;

    this->body->CreateFixture(&this->fixture);
    this->body->SetUserData(this);

    this->body->SetTransform(this->body->GetPosition(), info.angle);

    this->angle = info.angle;
    this->power = info.power;
    this->damageInfo = info.dmgInfo;
}

void Worms::Bullet::update(float dt) {
    if (!this->impulseApplied) {
        float32 mass = this->body->GetMass();  
        b2Vec2 impulses = {mass * float32(this->power * cos(this->angle * PI / 180.0f)),
                           mass * float32(this->power * sin(this->angle * PI / 180.0f))};
        b2Vec2 position = this->body->GetWorldCenter();
        this->body->ApplyLinearImpulse(impulses, position, true);
        this->impulseApplied = true;
    } else {
        b2Vec2 velocity = this->body->GetLinearVelocity();
        this->angle = atan2(velocity.y, velocity.x) * 180.0f / PI;
        if (this->angle < 0) {
            this->angle += 360.0f;
        }
    }
}

Math::Point<float> Worms::Bullet::getPosition() const {
    b2Vec2 p = this->body->GetPosition();
    return Math::Point<float>(p.x, p.y);
}

float Worms::Bullet::getAngle() const {
    return (this->angle >= 0 && this->angle < 90) ? this->angle + 360.0f : this->angle;
}

void Worms::Bullet::startContact() {
    this->numContacts++;
}

void Worms::Bullet::endContact() {
    if (this->numContacts > 0) {
        this->numContacts--;
    }
}

Worms::Bullet::~Bullet() {
    this->body->GetWorld()->DestroyBody(this->body);
}

bool Worms::Bullet::madeImpact() {
    return this->numContacts > 0;
}

Worms::DamageInfo Worms::Bullet::getDamageInfo() {
    return this->damageInfo;
}
