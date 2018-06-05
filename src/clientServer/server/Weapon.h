/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 28/05/18
 */

#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <GameStateMsg.h>
#include <memory>

#include "Bullet.h"
#include "Config.h"

namespace Worms {
class Player;
class Weapon {
   public:
    Weapon(const Game::Weapon::Config &config, Worm::WeaponID id, float angle);
    virtual ~Weapon() = default;

    const Worm::WeaponID &getWeaponID() const;
    /**
     * If was an event of startShot, then increase its power shot until
     * reach its limit.
     * @param dt
     */
    virtual void update(float dt) = 0;
    void increaseAngle();
    void decreaseAngle();
    float getAngle() const;
    virtual void startShot() = 0;
    virtual void endShot(Player &p, Physics &physics) = 0;
    virtual void setTimeout(uint8_t time) = 0;
    /**
     * sets bullet_ptr to null, and free its resources
     */
    void destroyBullet();

    std::shared_ptr<Bullet> getBullet() const;

   protected:
    bool increaseShotPower{false};
    float shotPower{0};
    Game::Weapon::Config config;
    Worm::WeaponID id;
    float angle{0};
    std::shared_ptr<Bullet> bullet{nullptr};

   private:
    /**
     * When weapons change, their own limit angles may crash the game.
     * To avoid this, this function checks and correct angles between changes.
     */
    void checkBoundaryAngles();
};
}  // namespace Worms

#endif  //_WEAPON_H__
