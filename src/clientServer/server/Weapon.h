/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 28/05/18
 */

#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <GameStateMsg.h>

#define MIN_ANGLE -90
#define MAX_ANGLE 84.375f
#define ANGLE_STEP 5.625f

#define MAX_SHOT_POWER 50

namespace Worms{
    class Player;
    class Weapon{
    public:

        Weapon() = default;
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
    };
} // namespace Worms

#endif //_WEAPON_H__
