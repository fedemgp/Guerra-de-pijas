/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 16/06/18
 */

#ifndef __AERIAL_ATTACK_H__
#define __AERIAL_ATTACK_H__

#include "Player.h"
#include "Weapon.h"

namespace Weapon{
class AerialAttack: public Worms::Weapon {
public:
    AerialAttack();
    ~AerialAttack() override = default;
    void update(float dt) override;
    void startShot(Worms::Player *player) override;
    void endShot() override;
    void setTimeout(uint8_t time) override;
    std::list<Worms::Bullet> onExplode(const Worms::Bullet &mainBullet,
                                       Worms::Physics &physics) override;
    void positionSelected(Worms::Player &p, Math::Point<float> point) override;

private:
    const uint8_t bulletsQuantity{0};
    const float missileSeparation{0};
};
}  // namespace Weapon


#endif //__AERIAL_ATTACK_H__
