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
    Weapon();
    ~Weapon() = default;

    const Worm::WeaponID &getWeaponID() const;
    void setWeapon(const Worm::WeaponID &id);
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
    void endShot(Player &p, Physics &physics);
    float getAngle() const;
    /**
     * sets bullet_ptr to null, and free its resources
     */
    void destroyBullet();

    std::shared_ptr<Bullet> getBullet() const;

private:
    /**
     * When weapons change, their own limit angles may crash the game.
     * To avoid this, this function checks and correct angles between changes.
     */
    void checkBoundaryAngles();
    bool increaseShotPower{false};
    uint16_t shotPower{0};
    Worm::WeaponID id{Worm::WeaponID::WBazooka};
    float angle{0};
    Game::Weapon::Config config;
    std::shared_ptr<Bullet> bullet{nullptr};
};
}  // namespace Worms

#endif  //_WEAPON_H__
