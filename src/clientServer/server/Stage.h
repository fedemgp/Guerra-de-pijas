/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __STAGE_H__
#define __STAGE_H__

#include <cstdint>
#include <vector>
#include "Point.h"

namespace Worms {
struct Girder {
    float length;
    float height;
    Math::Point<float> pos;
};

class Stage {
   public:
    uint8_t turnTime{3};

    Stage();
    ~Stage() = default;

    const std::vector<Math::Point<float>> &getWormPositions() const;
    const std::vector<Girder> &getGirders() const;

    float getHeight() const;
    float getWidth() const;

   private:
    std::vector<Math::Point<float>> playerPositions;
    std::vector<Girder> girders;
    float width{30.0f}, height{30.0f};
};
}  // namespace Worms

#endif  //__STAGE_H__
