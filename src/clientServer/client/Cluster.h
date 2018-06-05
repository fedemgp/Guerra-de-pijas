/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 04/06/18
 */

#ifndef __CLUSTER_H__
#define __CLUSTER_H__

#include <vector>

#include "PowerBar.h"
#include "Scope.h"
#include "Weapon.h"

#define CLUSTER_CENTER_FRAME 15

namespace Worm {
class Cluster : public Weapon {
   public:
    explicit Cluster(const GUI::GameTextureManager &textureManager);
    ~Cluster() = default;
    void update(float dt) override;
    void render(GUI::Position &p, GUI::Camera &cam, SDL_RendererFlip &flip) override;
    void setAngle(float angle, Direction d) override;
    void startShot() override;
    void endShot() override;

   private:
    ::Weapon::Scope scope;
    ::Weapon::PowerBar powerBar;
};
}  // namespace Worm

#endif  //__CLUSTER_H__
