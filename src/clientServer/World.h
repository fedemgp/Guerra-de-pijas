/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __WORLD_H__
#define __WORLD_H__

#include <vector>
#include "Point.h"

namespace Worms {

class World {
   public:
    World();
    ~World() = default;
    const std::vector<Math::Point<float>> &getWormPosition() const;
    float getHeight() const;
    float getWidth() const;

   private:
    std::vector<Math::Point<float>> playerPositions;
    float width{30.0f}, height{30.0f};
};
}  // namespace Worms

#endif  //__WORLD_H__
