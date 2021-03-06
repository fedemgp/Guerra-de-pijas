/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#define PLAYER_WIDTH 0.8f

#define PLAYER_HEIGHT 2.0f

#include <list>

#include "Config/Config.h"
#include "Config/P2PWeapon.h"
#include "Direction.h"
#include "GameStateMsg.h"
#include "Physics.h"
#include "Point.h"
#include "Stream.h"
#include "Team.h"
#include "TouchSensor.h"
#include "Weapons/Bullet.h"
#include "Weapons/Weapon.h"
#include "WormStates/PlayerState.h"

enum class PlayerState { movingRight, movingLeft, still };

namespace Worms {

class Player : public PhysicsEntity {
   public:
    Worm::Direction direction{Worm::Direction::left};
    Worm::Direction lastWalkDirection;
    std::uint16_t health{0};
    Math::Point<float> teleportPosition{0.0f, 0.0f};
    bool dyingDisconnected{false};

    explicit Player(Physics &physics);
    Player(Player &&player) noexcept;
    Player(Player &copy) = delete;

    ~Player();

    /* contact handlers */
    virtual void contactWith(PhysicsEntity &other, b2Contact &contact);

    bool isOnGround() const;

    /**
     * Updates its state, its weapon
     * @param dt
     */
    void update(float dt);
    void serialize(IO::Stream<IO::GameStateMsg> &s) const {}
    /**
     * @brief moves the player to newPos position
     * @param newPos
     */
    void setPosition(const Math::Point<float> &newPos);
    b2Vec2 getGroundNormal() const;
    void startContact(Worms::PhysicsEntity *physicsEntity, b2Contact &contact);

    /**
     * @brief asks box2D from current position.
     * @return
     */
    Math::Point<float> getPosition() const;
    /**
     * @brief given playerInput, changes its state (or its weapon) accordingly
     * @param pi
     */
    void handleState(IO::PlayerMsg pi);
    const std::shared_ptr<Worms::Weapon> getWeapon() const;
    Worm::StateID getStateId() const;
    void setState(Worm::StateID stateID);
    float getWeaponAngle() const;
    const Worm::WeaponID &getWeaponID() const;
    void setWeapon(const Worm::WeaponID &id);
    /**
     * @brief delegates on its weapon the action of increase the angle, if
     * the weapon handles it.
     */
    void increaseWeaponAngle();
    /**
     * @brief delegates on its weapon the action of decrease the angle, if
     * the weapon handles it.
     */
    void decreaseWeaponAngle();
    /**
     * @brief delegates on its weapon the action of starting a shot, increasing
     * its powerShot if it handles it
     */
    void startShot();
    /**
     * @brief creates a bullet that needs to be moved using getBullet()
     */
    void endShot();
    void acknowledgeDamage(Config::Bullet::DamageInfo damageInfo, Math::Point<float> epicenter);
    void acknowledgeDamage(const Config::P2PWeapon &info, Math::Point<float> shooterPosition,
                           Worm::Direction shooterDirection);
    void landDamage(float yDistance);
    void setTeamID(uint8_t team);
    void setTeam(Worms::Team *team);
    void increaseHealth(float extraPoints);
    uint8_t getTeam() const;
    void setId(uint8_t id);
    uint8_t getId() const;
    Physics &getPhysics();
    void setWeaponTimeout(uint8_t time);
    /**
     * Moves the bullets to the caller (the Game)
     * @return bullets
     */
    std::list<Bullet> getBullets();
    /**
     * Resets the weapon's powershot and erase every possible bullet
     * inside his container.
     */
    void reset();
    /**
     * calls weapon's onExplode and get new bullets if it is necesary.
     */
    std::list<Bullet> onExplode(const Bullet &bullet, Physics &physics);

    bool operator!=(const Player &other);
    bool operator==(const Player &other);

    void endShot(std::list<Worms::Bullet> &bullets);
    void die();

   private:
    b2Body *createBody(b2BodyType type);

    b2Body *body{nullptr};
    b2Body *body_kinematic{nullptr};
    TouchSensor *footSensor;

    std::shared_ptr<Worms::State> state{nullptr};
    std::shared_ptr<Worms::Weapon> weapon{nullptr};
    Physics &physics;
    const int waterLevel;
    uint8_t teamID;
    uint8_t id;
    std::list<Bullet> bullets;
    bool isP2PWeapon{false};
    b2Vec2 lastGroundNormal{0.0f, 0.0f};
    Team *team{nullptr};
};
}  // namespace Worms

#endif  //__PLAYER_H__
