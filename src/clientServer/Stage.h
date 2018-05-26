/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __STAGE_H__
#define __STAGE_H__

#include <vector>
#include "Point.h"

namespace Worms {

class Stage {
   public:
    Stage();
    ~Stage() = default;

    const std::vector<Math::Point<float>> &getWormPositions() const;
    const std::vector<Math::Point<float>> &getGirderPositions() const;

    float getHeight() const;
    float getWidth() const;

   private:
    std::vector<Math::Point<float>> playerPositions;
    std::vector<Math::Point<float>> girderPositions;
    float width{30.0f}, height{30.0f};
};
}  // namespace Worms

#endif  //__STAGE_H__
