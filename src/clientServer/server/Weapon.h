/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 28/05/18
 */

#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <GameStateMsg.h>

namespace Worms{
    class Weapon{
    public:
        Weapon() = default;
        ~Weapon() = default;
        const Worm::WeaponID &getWeaponID() const;
        void setWeaponID(const Worm::WeaponID &id);
    private:
        Worm::WeaponID id{Worm::WeaponID::WBazooka};
    };
} // namespace Worms

#endif //_WEAPON_H__
