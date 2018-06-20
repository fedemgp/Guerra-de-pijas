/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 16/06/18
 */

#ifndef __TNT_H__
#define __TNT_H__

#include "Weapon.h"

namespace Weapon {
class Dynamite : public Worms::Weapon {
   public:
    Dynamite();
    ~Dynamite() override = default;
    void update(float dt) override;
    void startShot(Worms::Player *player) override;
    void endShot() override;
    void setTimeout(uint8_t time) override;
    std::list<Worms::Bullet> onExplode(const Worms::Bullet &mainBullet,
                                       Worms::Physics &physics) override;
    void positionSelected(Worms::Player &p, Math::Point<float> point) override;
    void increaseAngle() override;
    void decreaseAngle() override;
};
}  // namespace Weapon

#endif  //__TNT_H__
