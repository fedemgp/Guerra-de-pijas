/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <Box2D/Box2D.h>
#include <iostream>

#include "AerialAttack.h"
#include "Banana.h"
#include "Bazooka.h"
#include "Cluster.h"
#include "Dead.h"
#include "Die.h"
#include "Drowning.h"
#include "Dynamite.h"
#include "Falling.h"
#include "Grenade.h"
#include "Hit.h"
#include "Holy.h"
#include "Land.h"
#include "Mortar.h"
#include "Physics.h"
#include "Player.h"
#include "PlayerBackFlipping.h"
#include "PlayerEndBackFlip.h"
#include "PlayerEndJump.h"
#include "PlayerJumping.h"
#include "PlayerStartBackFlip.h"
#include "PlayerStartJump.h"
#include "PlayerStill.h"
#include "PlayerWalk.h"
#include "Weapon.h"
#include "AerialAttack.h"
#include "Teleport.h"
#include "Teleporting.h"
#include "Teleported.h"

#define CONFIG Game::Config::getInstance()

Worms::Player::Player(Physics &physics)
    : PhysicsEntity(Worms::EntityID::EtWorm), physics(physics), waterLevel(CONFIG.getWaterLevel()) {
    /* creates 2 bodies so players cannot move each other */
    this->body = this->createBody(b2_dynamicBody);
    this->body_kinematic = this->createBody(b2_kinematicBody);

    b2PolygonShape shape;
    shape.SetAsBox(PLAYER_WIDTH / 2, 0.2f, b2Vec2{0, -PLAYER_HEIGHT / 2}, 0);

    /* allocated in heap because it's address shouldn't change */
    this->footSensor = new TouchSensor{*this->body, shape, -1};

    this->setState(Worm::StateID::Falling);
    this->weapon = std::shared_ptr<Worms::Weapon>(new ::Weapon::Bazooka(0.0f));
}

Worms::Player::~Player() {
    delete this->footSensor;
}

/**
 * @brief "Not equal" operator.
 *
 * @param other Other instance to compare.
 * @return true if not equal.
 */
bool Worms::Player::operator!=(const Player &other) {
    return !(*this == other);
}

/**
 * @brief Comparisson operator.
 *
 * @param other Other instance to compare.
 * @return true if equal.
 */
bool Worms::Player::operator==(const Player &other) {
    return (this->id == other.id) && (this->team == other.team);
}

/**
 * @brief Handles player-entity contact.
 *
 * @param other Other player that made contact.
 * @param contact box2D collision contact.
 */
void Worms::Player::contactWith(PhysicsEntity &entity, b2Contact &contact) {
    if (entity.getEntityId() != Worms::EntityID::EtWorm) {
        return;
    }

    /* checks if it's the player itself */
    if (&entity == this) {
        /* checks if it's the kinematic and dynamic bodies cooliding */
        if (contact.GetFixtureA()->GetBody()->GetType() !=
            contact.GetFixtureB()->GetBody()->GetType()) {
            contact.SetEnabled(false);
        }
    }
}

void Worms::Player::update(float dt) {
    /* sets the kinematic body to the position of the dynamic body */
    this->body_kinematic->SetTransform(this->body->GetTransform().p, this->body->GetAngle());

    this->state->update(*this, dt, this->body);
    this->weapon->update(dt);

    if (this->getPosition().y <= this->waterLevel && this->getStateId() != Worm::StateID::Dead &&
        this->getStateId() != Worm::StateID::Drowning) {
        this->health = 0.0f;
        if (this->getStateId() == Worm::StateID::Hit) {
            this->notify(*this, Event::EndHit);
        }
        this->setState(Worm::StateID::Drowning);
        this->notify(*this, Event::Drowning);
    }
}

/**
 * @brief Whether the player is touching the ground or not.
 *
 * @return true is touching the ground.
 */
bool Worms::Player::isOnGround() const {
    return this->footSensor->isActive();
}

void Worms::Player::setPosition(const Math::Point<float> &new_pos) {
    this->body->SetTransform(b2Vec2(new_pos.x, new_pos.y), body->GetAngle());
}

Math::Point<float> Worms::Player::getPosition() const {
    const b2Vec2 &pos = this->body->GetPosition();
    return Math::Point<float>{pos.x, pos.y};
}

Worm::StateID Worms::Player::getStateId() const {
    return this->state->getState();
}

void Worms::Player::handleState(IO::PlayerMsg pi) {
    switch (pi.input) {
        case IO::PlayerInput::moveLeft:
            this->state->moveLeft(*this);
            break;
        case IO::PlayerInput::moveRight:
            this->state->moveRight(*this);
            break;
        case IO::PlayerInput::startJump:
            this->state->jump(*this);
            break;
        case IO::PlayerInput::startBackFlip:
            this->state->backFlip(*this);
            break;
        case IO::PlayerInput::stopMove:
            this->state->stopMove(*this);
            break;
        case IO::PlayerInput::bazooka:
            this->state->bazooka(*this);
            break;
        case IO::PlayerInput::grenade:
            this->state->grenade(*this);
            break;
        case IO::PlayerInput::cluster:
            this->state->cluster(*this);
            break;
        case IO::PlayerInput::mortar:
            this->state->mortar(*this);
            break;
        case IO::PlayerInput::banana:
            this->state->banana(*this);
            break;
        case IO::PlayerInput::holy:
            this->state->holy(*this);
            break;
        case IO::PlayerInput::moveNone:
            break;
        case IO::PlayerInput::pointUp:
            this->state->pointUp(*this);
            break;
        case IO::PlayerInput::pointDown:
            this->state->pointDown(*this);
            break;
        case IO::PlayerInput::startShot:
            this->state->startShot(*this);
            break;
        case IO::PlayerInput::endShot:
            this->state->endShot(*this);
            break;
        case IO::PlayerInput::timeout1:
            this->state->setTimeout(*this, 1);
            break;
        case IO::PlayerInput::timeout2:
            this->state->setTimeout(*this, 2);
            break;
        case IO::PlayerInput::timeout3:
            this->state->setTimeout(*this, 3);
            break;
        case IO::PlayerInput::timeout4:
            this->state->setTimeout(*this, 4);
            break;
        case IO::PlayerInput::timeout5:
            this->state->setTimeout(*this, 5);
            break;
        case IO::PlayerInput::positionSelected:
            this->weapon->positionSelected(*this, pi.position);
            break;
        case IO::PlayerInput::aerialAttack:
            this->state->aerialAttack(*this);
            break;
        case IO::PlayerInput::dynamite:
            this->state->dynamite(*this);
            break;
        case IO::PlayerInput::teleport:
            this->state->teleport(*this);
            break;
    }
}

void Worms::Player::setState(Worm::StateID stateID) {
    if (this->state == nullptr || this->state->getState() != stateID) {
        /* creates the right state type */
        this->body->SetType(b2_dynamicBody);
        switch (stateID) {
            case Worm::StateID::Still:
                //                this->body->SetType(b2_staticBody);
                this->state = std::shared_ptr<State>(new Still());
                break;
            case Worm::StateID::Walk:
                this->state = std::shared_ptr<State>(new Walk());
                break;
            case Worm::StateID::StartJump:
                this->state = std::shared_ptr<State>(new StartJump());
                break;
            case Worm::StateID::Jumping:
                this->state = std::shared_ptr<State>(new Jumping(this->getPosition()));
                break;
            case Worm::StateID::EndJump:
                this->state = std::shared_ptr<State>(new EndJump());
                break;
            case Worm::StateID::StartBackFlip:
                this->state = std::shared_ptr<State>(new StartBackFlip());
                break;
            case Worm::StateID::BackFlipping:
                this->state = std::shared_ptr<State>(new BackFlipping(this->getPosition()));
                break;
            case Worm::StateID::EndBackFlip:
                this->state = std::shared_ptr<State>(new EndBackFlip());
                break;
            case Worm::StateID::Falling:
                this->state = std::shared_ptr<State>(new Falling(this->getPosition()));
                break;
            case Worm::StateID::Land:
                this->state = std::shared_ptr<State>(new Land());
                break;
            case Worm::StateID::Teleporting:
                this->state = std::shared_ptr<State>(new Teleporting(this->teleportPosition));
                break;
            case Worm::StateID::Teleported:
                this->state = std::shared_ptr<State>(new Teleported());
                break;
            case Worm::StateID::Hit:
                this->state = std::shared_ptr<State>(new Hit());
                break;
            case Worm::StateID::Die:
                this->notify(*this, Event::Dying);
                this->state = std::shared_ptr<State>(new Die());
                break;
            case Worm::StateID::Drowning:
                this->state = std::shared_ptr<State>(new Drowning());
                break;
            case Worm::StateID::Dead:
                this->state = std::shared_ptr<State>(new Dead());
                this->body->SetType(b2_staticBody);
                break;
        }
    }
}

std::list<Worms::Bullet> Worms::Player::getBullets() {
    return std::move(this->bullets);
}

void Worms::Player::acknowledgeDamage(Game::Bullet::DamageInfo damageInfo,
                                      Math::Point<float> epicenter) {
    if (this->getStateId() != Worm::StateID::Dead) {
        double distanceToEpicenter = this->getPosition().distance(epicenter);
        if (distanceToEpicenter <= damageInfo.radius) {
            this->body->SetType(b2_dynamicBody);
            double inflictedDamage =
                (1.0f - (distanceToEpicenter / (damageInfo.radius * 1.01f))) * damageInfo.damage;
            this->health -= inflictedDamage;

            Math::Point<float> positionToEpicenter = this->getPosition() - epicenter;
            float xImpactDirection = (positionToEpicenter.x > 0) - (positionToEpicenter.x < 0);
            float yImpactDirection = (positionToEpicenter.y > 0) - (positionToEpicenter.y < 0);
            float32 mass = this->body->GetMass();
            b2Vec2 impulses = {
                mass * float32(inflictedDamage) * xImpactDirection * damageInfo.impulseDampingRatio,
                mass * float32(inflictedDamage) * yImpactDirection *
                    damageInfo.impulseDampingRatio};
            b2Vec2 position = this->body->GetWorldCenter();
            this->body->ApplyLinearImpulse(impulses, position, true);
            this->notify(*this, Event::Hit);
            this->setState(Worm::StateID::Hit);
            this->health = (this->health < 0) ? 0 : this->health;
        }
    }
}

float Worms::Player::getWeaponAngle() const {
    return this->weapon->getAngle();
}

const Worm::WeaponID &Worms::Player::getWeaponID() const {
    return this->weapon->getWeaponID();
}
// TODO add creation time in Team, and in this method ask for it. So that the
// team tracks weapons quantity
void Worms::Player::setWeapon(const Worm::WeaponID &id) {
    if (this->weapon->getWeaponID() != id) {
        // keep the last angle
        float lastAngle = this->weapon->getAngle();
        switch (id) {
            case Worm::WeaponID::WBazooka:
                this->weapon = std::shared_ptr<Worms::Weapon>(new ::Weapon::Bazooka(lastAngle));
                break;
            case Worm::WeaponID::WGrenade:
                this->weapon = std::shared_ptr<Worms::Weapon>(new ::Weapon::Grenade(lastAngle));
                break;
            case Worm::WeaponID::WCluster:
                this->weapon = std::shared_ptr<Worms::Weapon>(new ::Weapon::Cluster(lastAngle));
                break;
            case Worm::WeaponID::WMortar:
                this->weapon = std::shared_ptr<Worms::Weapon>(new ::Weapon::Mortar(lastAngle));
                break;
            case Worm::WeaponID::WBanana:
                this->weapon = std::shared_ptr<Worms::Weapon>(new ::Weapon::Banana(lastAngle));
                break;
            case Worm::WeaponID::WHoly:
                this->weapon = std::shared_ptr<Worms::Weapon>(new ::Weapon::Holy(lastAngle));
                break;
            case Worm::WeaponID::WAerial:
                this->weapon = std::shared_ptr<Worms::Weapon>(new ::Weapon::AerialAttack());
                break;
            case Worm::WeaponID::WDynamite:
                this->weapon = std::shared_ptr<Worms::Weapon>(new ::Weapon::Dynamite());
                break;
            case Worm::WeaponID::WTeleport:
                this->weapon = std::shared_ptr<Worms::Weapon>(new ::Weapon::Teleport());
                break;
            case Worm::WeaponID::WNone:
                break;
            case Worm::WeaponID::WExplode:
                break;
            case Worm::WeaponID::WFragment:
                break;
        }
    }
}

void Worms::Player::increaseWeaponAngle() {
    this->weapon->increaseAngle();
}

void Worms::Player::decreaseWeaponAngle() {
    this->weapon->decreaseAngle();
}

void Worms::Player::startShot() {
    this->weapon->startShot(this);
}

void Worms::Player::endShot() {
    Math::Point<float> position = this->getPosition();
    float safeNonContactDistance =
        sqrt((PLAYER_WIDTH / 2) * (PLAYER_WIDTH / 2) + (PLAYER_HEIGHT / 2) * (PLAYER_HEIGHT / 2));
    BulletInfo info = this->weapon->getBulletInfo();
    info.point = position;
    info.safeNonContactDistance = safeNonContactDistance;
    if (this->direction == Worms::Direction::right) {
        if (info.angle < 0.0f) {
            info.angle += 360.0f;
        }
    } else {
        info.angle = 180.0f - info.angle;
    }
    this->bullets.emplace_back(info, this->physics, this->weapon->getWeaponID());
    this->weapon->endShot();
    this->notify(*this, Event::Shot);
}

void Worms::Player::endShot(std::list<Worms::Bullet> &bullets) {
    this->bullets = std::move(bullets);
    this->notify(*this, Event::Shot);
}

void Worms::Player::setTeam(uint8_t team) {
    this->team = team;
}

void Worms::Player::increaseHealth(float percentage) {
    this->health += (percentage / 100.0f) * this->health;
}

uint8_t Worms::Player::getTeam() const {
    return this->team;
}

void Worms::Player::setId(uint8_t id) {
    this->id = id;
}

uint8_t Worms::Player::getId() const {
    return this->id;
}

void Worms::Player::setWeaponTimeout(uint8_t time) {
    this->weapon->setTimeout(time);
}

void Worms::Player::landDamage(float yDistance) {
    if (yDistance > CONFIG.getSafeFallDistance()) {
        this->health -=
            (yDistance > CONFIG.getMaxFallDamage()) ? CONFIG.getMaxFallDamage() : yDistance;
        if (this->health > 0.0f) {
            this->notify(*this, Event::DamageOnLanding);
        }
    }
}

/**
 * @brief Creates a player's body with the given type.
 *
 * @param type Body type.
 * @return Created body.
 */
b2Body *Worms::Player::createBody(b2BodyType type) {
    b2BodyDef bodyDef;
    bodyDef.type = type;
    bodyDef.position.Set(0.0f, 0.0f);
    bodyDef.fixedRotation = true;
    b2Body *new_body = this->physics.createBody(bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(PLAYER_WIDTH / 2, PLAYER_HEIGHT / 2);
    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = 1.0f;
    fixture.restitution = 0.1f;
    fixture.friction = 1.0f;
    new_body->CreateFixture(&fixture);
    new_body->SetUserData(this);
    return new_body;
}

std::list<Worms::Bullet> Worms::Player::onExplode(const Bullet &b, Physics &physics) {
    return std::move(this->weapon->onExplode(b, physics));
}

void Worms::Player::reset() {
    this->weapon->endShot();
    this->bullets.erase(this->bullets.begin(), this->bullets.end());
}

Worms::Physics &Worms::Player::getPhysics() {
    return this->physics;
}
