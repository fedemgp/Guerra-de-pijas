//
// Created by rodrigo on 16/06/18.
//

#ifndef INC_4_WORMS_TELEPORT_H
#define INC_4_WORMS_TELEPORT_H

#include "Player.h"
#include "Weapon.h"

namespace Weapon {
class Teleport : public Worms::Weapon {
   public:
    Teleport();
    ~Teleport() override = default;
    void update(float dt) override;
    void increaseAngle() override;
    void decreaseAngle() override;
    void startShot(Worms::Player *player) override;
    void endShot() override;
    void setTimeout(uint8_t time) override;
    std::list<Worms::Bullet> onExplode(const Worms::Bullet &mainBullet,
                                       Worms::Physics &physics) override;
    void positionSelected(Worms::Player &p, Math::Point<float> point) override;
};
}  // namespace Weapon

#endif  // INC_4_WORMS_TELEPORT_H
