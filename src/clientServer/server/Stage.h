/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 18/05/18
 */

#ifndef __STAGE_H__
#define __STAGE_H__

#include <cstdint>
#include <vector>

#include "Config.h"
#include "Point.h"

namespace Worms {
struct Girder {
    float length;
    float height;
    Math::Point<float> pos;
};

struct WormData {
    uint16_t health;
    Math::Point<float> position;
};

class Stage {
   public:
    uint8_t turnTime{Game::Config::getInstance().getTurnTime()};

    Stage();
    ~Stage() = default;

    const std::vector<WormData> &getWorms() const;
    const std::vector<Girder> &getGirders() const;

    float getHeight() const;
    float getWidth() const;
    uint8_t getNumTeams();

   private:
    std::vector<WormData> players;
    std::vector<Girder> girders;
    float width{Game::Config::getInstance().getGameWidth()};
    float height{Game::Config::getInstance().getGameHeight()};
    uint8_t numTeams{Game::Config::getInstance().getNumTeams()};
};
}  // namespace Worms

#endif  //__STAGE_H__
