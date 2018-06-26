/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#include <Box2D/Box2D.h>
#include <iostream>

#include "Direction.h"
#include "Girder.h"
#include "Physics.h"
#include "Player.h"
#include "Weapons/AerialAttack.h"
#include "Weapons/Banana.h"
#include "Weapons/BaseballBat.h"
#include "Weapons/Bazooka.h"
#include "Weapons/Cluster.h"
#include "Weapons/Dynamite.h"
#include "Weapons/Grenade.h"
#include "Weapons/Holy.h"
#include "Weapons/Mortar.h"
#include "Weapons/Teleport.h"
#include "Weapons/Weapon.h"
#include "WormStates/BackFlipping.h"
#include "WormStates/Dead.h"
#include "WormStates/Die.h"
#include "WormStates/Drowning.h"
#include "WormStates/EndBackFlip.h"
#include "WormStates/EndJump.h"
#include "WormStates/Falling.h"
#include "WormStates/Hit.h"
#include "WormStates/Jumping.h"
#include "WormStates/Land.h"
#include "WormStates/Sliding.h"
#include "WormStates/StartBackFlip.h"
#include "WormStates/StartJump.h"
#include "WormStates/Still.h"
#include "WormStates/Teleported.h"
#include "WormStates/Teleporting.h"
#include "WormStates/Walk.h"
#include "WormStates/Batting.h"
#include "Weapons/WeaponNone.h"

#define CONFIG Game::Config::getInstance()

Worms::Player::Player(Physics &physics)
    : PhysicsEntity(Worms::EntityID::EtWorm), physics(physics), waterLevel(CONFIG.getWaterLevel()) {
    /* creates 2 bodies so players cannot move each other */
    this->body = this->createBody(b2_dynamicBody);
    this->body_kinematic = this->createBody(b2_kinematicBody);

    /* creates the sensor as a circle */
    b2CircleShape sensorShape;
    sensorShape.m_radius = PLAYER_HEIGHT / 4;
    sensorShape.m_p.Set(0.0f, -PLAYER_HEIGHT / 4 - 0.2);

    /* allocated in heap because it's address shouldn't change */
    this->footSensor = new TouchSensor{*this->body, sensorShape};
    this->footSensor->ignore(*this);

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
    return (this->id == other.id) && (this->teamID == other.teamID);
}

/**
 * @brief Handles player-entity contact.
 *
 * @param other Other player that made contact.
 * @param contact box2D collision contact.
 */
void Worms::Player::contactWith(PhysicsEntity &entity, b2Contact &contact) {
    if (entity.getEntityId() == Worms::EntityID::EtGirder) {
        Worms::Girder &girder = dynamic_cast<Worms::Girder &>(entity);
        if (std::abs(girder.angle) > PI / 4.0f) {
            this->lastGroundNormal = contact.GetManifold()->localNormal;
        } else {
            this->lastGroundNormal = {0.0f, 0.1f};
        }
    }

    if (entity.getEntityId() != Worms::EntityID::EtWorm) {
        return;
    }

    /* checks if it's the player itself */
    if (&entity == this) {
        /* checks if it's the kinematic and dynamic bodies colliding */
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
    } else if (this->isOnGround()) {
        /* checks if the ground slope is too tilted */
        try {
            b2Vec2 normal = this->getGroundNormal();
            float slope = std::abs(std::atan2(normal.y, normal.x));
            if ((slope < PI / 4.0f) || (slope > (PI * 3.0f) / 4.0f)) {
                if (this->getStateId() == Worm::StateID::Hit) {
                    this->notify(*this, Event::EndHit);
                }
                this->setState(Worm::StateID::Sliding);
                return;
            }
        } catch (const Exception &e) {
        }
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

/**
 * @brief Returns a unit vector with the direction normal to the floor where the player is standing.
 *
 * @return b2Vec2 Floor normal.
 */
b2Vec2 Worms::Player::getGroundNormal() const {
    for (auto &contact : *this->footSensor) {
        if (contact.first->getEntityId() == Worms::EntityID::EtGirder) {
            return this->lastGroundNormal;
        }
    }
    throw Exception{"No ground normal"};
}

void Worms::Player::startContact(Worms::PhysicsEntity *physicsEntity, b2Contact &contact) {}

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
        case IO::PlayerInput::baseballBat:
            this->state->baseballBat(*this);
            break;
        case IO::PlayerInput::teleport:
            this->state->teleport(*this);
            break;
        default:
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
            case Worm::StateID::Batting:
                this->state = std::shared_ptr<State>(new Batting());
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
            case Worm::StateID::Sliding:
                this->notify(*this, Event::WormFalling);
                this->state = std::shared_ptr<State>(new Sliding());
                break;
        }
    }
}

std::list<Worms::Bullet> Worms::Player::getBullets() {
    return std::move(this->bullets);
}

void Worms::Player::acknowledgeDamage(Config::Bullet::DamageInfo damageInfo,
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

void Worms::Player::acknowledgeDamage(const Config::P2PWeapon &info,
                                      Math::Point<float> shooterPosition,
                                      Worm::Direction shooterDirection) {
    if (this->getStateId() != Worm::StateID::Dead) {
        if ((shooterDirection == Worm::Direction::right &&
             this->getPosition().x - shooterPosition.x > 0) ||
            (shooterDirection == Worm::Direction::left &&
             this->getPosition().x - shooterPosition.x < 0)) {
            double distanceToTheWeapon = this->getPosition().distance(info.position);
            if (distanceToTheWeapon <= info.dmgInfo.radius && distanceToTheWeapon > 0) {
                this->body->SetType(b2_dynamicBody);
                this->health -= info.dmgInfo.damage;
                this->health = (this->health < 0) ? 0 : this->health;

                float32 mass = this->body->GetMass();
                Math::Point<float> direction{0, 0};
                direction.x = info.dmgInfo.radius * cos(info.angle * PI / 180.0f);
                direction.y = info.dmgInfo.radius * sin(info.angle * PI / 180.0f);
                Math::Point<float> positionToShooter = this->getPosition() - shooterPosition;
                float xImpactDirection = (positionToShooter.x > 0) - (positionToShooter.x < 0);
                float yImpactDirection = (direction.y > 0) - (direction.y < 0);
                b2Vec2 impulses = {mass * float32(info.dmgInfo.damage) * direction.x *
                                       xImpactDirection * info.dmgInfo.impulseDampingRatio,
                                   mass * float32(info.dmgInfo.damage) * direction.y *
                                       yImpactDirection * info.dmgInfo.impulseDampingRatio};

                this->body->ApplyLinearImpulse(impulses, this->body->GetWorldCenter(), true);
                this->notify(*this, Event::Hit);
                this->setState(Worm::StateID::Hit);
            }
        }
    }
}

float Worms::Player::getWeaponAngle() const {
    return this->weapon->getAngle();
}

const Worm::WeaponID &Worms::Player::getWeaponID() const {
    return this->weapon->getWeaponID();
}

void Worms::Player::setWeapon(const Worm::WeaponID &id) {
    // keep the last angle
    float lastAngle = this->weapon->getAngle();
    this->weapon = this->team->getWeapon(id);
    this->weapon->setAngle(lastAngle);
    this->isP2PWeapon = this->weapon->isP2PWeapon();
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
    if (this->weapon->getWeaponID() != Worm::WeaponID::WTeleport &&
        this->weapon->getWeaponID() != Worm::WeaponID::WAerial &&
            this->weapon->getWeaponID() != Worm::WeaponID::WNone) {
        if (!this->isP2PWeapon) {
            Math::Point<float> position = this->getPosition();
            float safeNonContactDistance = sqrt((PLAYER_WIDTH / 2) * (PLAYER_WIDTH / 2) +
                                                (PLAYER_HEIGHT / 2) * (PLAYER_HEIGHT / 2)) + 0.1;
            BulletInfo info = this->weapon->getBulletInfo();
            info.point = position;
            info.safeNonContactDistance = safeNonContactDistance;
            if (this->direction == Worm::Direction::right) {
                if (info.angle < 0.0f) {
                    info.angle += 360.0f;
                }
            } else {
                info.angle = 180.0f - info.angle;
            }
            this->bullets.emplace_back(info, this->physics, this->weapon->getWeaponID());
            this->weapon->endShot();
            this->notify(*this, Event::Shot);
        } else {
            this->setState(Worm::StateID::Batting);
            this->notify(*this, Event::P2PWeaponUsed);
        }
        this->team->weaponUsed(this->getWeaponID());
    }
}

void Worms::Player::endShot(std::list<Worms::Bullet> &bullets) {
    this->bullets = std::move(bullets);
    this->notify(*this, Event::Shot);
    this->team->weaponUsed(this->getWeaponID());
}

void Worms::Player::setTeamID(uint8_t team) {
    this->teamID = team;
}

void Worms::Player::increaseHealth(float percentage) {
    this->health += (percentage / 100.0f) * this->health;
}

uint8_t Worms::Player::getTeam() const {
    return this->teamID;
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
    /* the players consists of a rectangle as the upper part of the body and a cicle for the
     * bottom */
    b2BodyDef bodyDef;
    bodyDef.type = type;
    bodyDef.position.Set(0.0f, 0.0f);
    bodyDef.fixedRotation = true;
    b2Body *new_body = this->physics.createBody(bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(PLAYER_WIDTH / 2, PLAYER_HEIGHT / 4, b2Vec2{0.0f, PLAYER_HEIGHT / 4}, 0.0f);

    /* creates the upper square */
    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = 1.0f;
    fixture.restitution = 0.1f;
    fixture.friction = 1.0f;
    new_body->CreateFixture(&fixture);

    /* creates the bottom circle */
    b2CircleShape bottom;
    bottom.m_radius = PLAYER_HEIGHT / 4;
    bottom.m_p.Set(0.0f, -PLAYER_HEIGHT / 4);
    fixture.shape = &bottom;
    new_body->CreateFixture(&fixture);

    new_body->SetUserData(this);
    return new_body;
}

std::list<Worms::Bullet> Worms::Player::onExplode(const Bullet &b, Physics &physics) {
    return std::move(this->weapon->onExplode(b, physics));
}

void Worms::Player::reset() {
    this->weapon->endShot();
    /*
     * If the weapon has no more ammunition, returns weaponNone
     */
    this->setWeapon(this->getWeaponID());
    this->bullets.erase(this->bullets.begin(), this->bullets.end());
}

Worms::Physics &Worms::Player::getPhysics() {
    return this->physics;
}

const std::shared_ptr<Worms::Weapon> Worms::Player::getWeapon() const {
    return this->weapon;
}

void Worms::Player::setTeam(Worms::Team *team){
    this->team = team;
}

Worms::Player::Player(Worms::Player &&player) noexcept: PhysicsEntity(std::move(player)), physics(player.physics), waterLevel(player.waterLevel) {

    this->body = player.body;
    this->body_kinematic = player.body_kinematic;
    this->footSensor = player.footSensor;

    this->state = player.state;
    this->weapon = player.weapon;
    this->team = player.team;
    this->id = player.id;
    this->bullets = std::move(player.bullets);

    player.body = nullptr;
    player.body_kinematic = nullptr;
    player.footSensor = nullptr;
    player.state = nullptr;
    player.weapon = nullptr;
    player.team = 0;
    player.id = 0;
}

void Worms::Player::die() {
    this->setState(Worm::StateID::Die);
    this->health = 0;
    this->dyingDisconnected = true;
    this->notify(*this, Event::DyingDueToDisconnection);
}
