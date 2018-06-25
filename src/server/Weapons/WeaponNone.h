/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 24/06/18
 */

#ifndef __WEAPON_NONE_H__
#define __WEAPON_NONE_H__

#include "Weapon.h"

namespace Weapon {
class WeaponNone : public Worms::Weapon {
   public:
    WeaponNone();
    ~WeaponNone() override = default;
    void update(float dt) override{};
    void increaseAngle() override{};
    void decreaseAngle() override{};
    void checkBoundaryAngles() override{};
    void startShot(Worms::Player *player) override{};
    void endShot() override{};
    void setTimeout(uint8_t time) override{};
    std::list<Worms::Bullet> onExplode(const Worms::Bullet &mainBullet,
                                       Worms::Physics &physics) override;
    void positionSelected(Worms::Player &p, Math::Point<float> point) override{};
};
}  // namespace Weapon

#endif  //__WEAPON_NONE_H__
