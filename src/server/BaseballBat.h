//
// Created by rodrigo on 16/06/18.
//

#ifndef INC_4_WORMS_BASEBALLBAT_H
#define INC_4_WORMS_BASEBALLBAT_H

#include "Weapon.h"

namespace Weapon {
class BaseballBat : public Worms::Weapon {
   public:
    BaseballBat(float angle);
    ~BaseballBat() = default;
    void update(float dt) override;
    void startShot(Worms::Player *player) override;
    void endShot() override;
    void setTimeout(uint8_t time) override;
    std::list<Worms::Bullet> onExplode(const Worms::Bullet &mainBullet,
                                       Worms::Physics &physics) override;
    void positionSelected(Worms::Player &p, Math::Point<float> point) override;
    Config::P2PWeapon &getWeaponInfo();

   private:
    Config::P2PWeapon weaponInfo;
};
}  // namespace Weapon

#endif  // INC_4_WORMS_BASEBALLBAT_H
