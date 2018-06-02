/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 28/05/18
 */

#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <GameStateMsg.h>

namespace Worms {
class Player;
class Weapon {
   public:
    Weapon();
    ~Weapon() = default;

    const Worm::WeaponID &getWeaponID() const;
    void setWeaponID(const Worm::WeaponID &id);
    /**
     * If was an event of startShot, then increase its power shot until
     * reach its limit.
     * @param dt
     */
    void update(float dt);
    void increaseAngle();
    void decreaseAngle();
    /**
     * inits the increasing of the power shot.
     */
    void startShot();
    /**
     * calls Player::shoot(float powerShot) to instante a bullet.
     * @param p
     */
    void endShot(Player &p);
    float getAngle() const;

   private:
    bool increaseShotPower{false};
    int shotPower{0};
    Worm::WeaponID id{Worm::WeaponID::WBazooka};
    float angle{0};
    const float minAngle;
    const float maxAngle;
    const float angleStep;
    const uint16_t maxPowerShot;
};
}  // namespace Worms

#endif  //_WEAPON_H__
