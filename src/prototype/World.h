#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Point.h"

namespace Worms {

    class World {
    public:
        World() {
            this->player_positions.emplace_back(Math::Point<float>{0.0f, 15.0f});
        }

        ~World() {}

        const std::vector<Math::Point<float>> &get_worm_positions() const {
            return this->player_positions;
        }

        float get_height() const {
            return this->height;
        }

        float get_width() const {
            return this->width;
        }

    private:
        std::vector<Math::Point<float>> player_positions;
        float width{30.0f}, height{30.0f};
    };

}

#endif //WORLD_H
