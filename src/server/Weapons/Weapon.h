/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 28/05/18
 */

#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <GameStateMsg.h>
#include <list>
#include <memory>

#include "../Config/Config.h"
#include "Bullet.h"
#include "../Config/WeaponConfig.h"

namespace Worms {
class Player;
class Weapon {
   public:
    Weapon(const Config::Weapon &config, Worm::WeaponID id, float angle);
    virtual ~Weapon() = default;

    const Worm::WeaponID &getWeaponID() const;
    /**
     * If was an event of startShot, then increase its power shot until
     * reach its limit.
     * @param dt
     */
    virtual void update(float dt) = 0;
    /**
     * @brief increases the angle of the aim. If the angle exceeds the limit
     * then it will be changed to the maximum possible
     */
    virtual void increaseAngle();
    /**
     * @brief decreases the angle of the aim. If the angle exceeds the limit
     * then it will be changed to the maximum possible
     */
    virtual void decreaseAngle();
    float getAngle() const;
    void setAngle(float angle);
    virtual void startShot(Worms::Player *player) = 0;
    virtual void endShot() = 0;
    BulletInfo getBulletInfo();
    virtual void setTimeout(uint8_t time) = 0;
    /**
     * @brief check if the weapon is person to preson or not
     * @return
     */
    bool isP2PWeapon();
    /**
     * Used by te remote control weapons. Sends to the weapon the coordinates
     * of the deploy of the bullets, and a reference of Player so that the
     * weapons, if they are remote control. calls the appropiate method.
     * @param player to call deploy method (if the weapon has this feature)
     * @param point
     */
    virtual void positionSelected(Worms::Player &p, Math::Point<float> point) = 0;
    /**
     * Function that returns, using move semantics, a list of bullets
     * depending on weapon's behavior after the main bullet explode.
     * @return
     */
    virtual std::list<Worms::Bullet> onExplode(const Worms::Bullet &mainBullet,
                                               Worms::Physics &physics) = 0;

   protected:
    bool increaseShotPower{false};
    float shotPower{0};
    bool isP2P{false};
    const Config::Weapon &config;
    Worm::WeaponID id;
    float angle{0};
    uint8_t timeLimit;

   private:
    /**
     * When weapons change, their own limit angles may crash the game.
     * To avoid this, this function checks and correct angles between changes.
     */
    virtual void checkBoundaryAngles();
};
}  // namespace Worms

#endif  //_WEAPON_H__
