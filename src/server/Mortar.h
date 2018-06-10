/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 03/06/18
 */

#ifndef __Mortar_H__
#define __Mortar_H__

#include "Weapon.h"

namespace Weapon {
class Mortar : public Worms::Weapon {
   public:
    Mortar(float angle);
    ~Mortar() override = default;
    void update(float dt) override;
    void startShot() override;
    void endShot() override;
    void setTimeout(uint8_t time) override;
    std::list<Worms::Bullet> onExplode(const Worms::Bullet &bullet, Worms::Physics &physics) override;
    void positionSelected(Worms::Player &p, Math::Point<float> point) override;

private:
    const Game::Weapon::Config &fragmentConfig;
};
}  // namespace Weapon

#endif  //__Mortar_H__
