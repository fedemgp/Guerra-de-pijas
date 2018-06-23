/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __STAGE_H__
#define __STAGE_H__

#include <cstdint>
#include <string>
#include <vector>

#include "Point.h"
#include <yaml-cpp/include/yaml-cpp/yaml.h>

namespace Worms {
struct GirderData {
    float length;
    float height;
    float angle;
    Math::Point<float> pos;
};

struct WormData {
    uint16_t health;
    Math::Point<float> position;
};

class Stage {
   public:
    static Stage fromFile(const std::string &filename);

    uint8_t turnTime{10};

    Stage();
    ~Stage() = default;

    const std::vector<WormData> &getWorms() const;
    const std::vector<GirderData> &getGirders() const;

    float getHeight() const;
    float getWidth() const;

   private:
    std::vector<WormData> players;
    std::vector<GirderData> girders;
    float width{100.0f};
    float height{30.0f};
};
}  // namespace Worms

#endif  //__STAGE_H__
