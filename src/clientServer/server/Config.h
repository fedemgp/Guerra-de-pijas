/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 01/06/18
 */

#ifndef __GAMECONFIG_H__
#define __GAMECONFIG_H__

#include <stdint-gcc.h>
#include "GameConstants.h"
#include "Point.h"

namespace Math{
    using Vector = Math::Point<float>;
}

namespace Game{
    /**
     *  Singleton class with all the game configuration (Velocity constants,
     *  Weapons attributes, etc)
     */
    class Config{
    public:
        static Config &getInstance();
        ~Config() = default;

        const Math::Vector getJumpVelocity() const;
        const Math::Vector getBackflipVelocity() const;
        const float getStartJumpTime() const;
        const float getLandTime() const;

        const float getWalkVelocity() const;

        const uint8_t getTurnTime() const;
        const float getExtraTurnTime() const;
        const uint8_t getNumTeams() const;
        const float getGameWidth() const;
        const float getGameHeight() const;
        const float getDyingTime() const;
        const float getDrowningTime() const;
        const int getWaterLevel() const;
        const uint16_t getWormHealth() const;

        const float getBazookaDmg() const;
        const float getBazookaDmgRadius() const;
        const float getMinAngle() const;
        const float getMaxAngle() const;
        const float getAngleStep() const;
        const uint16_t getMaxShotPower() const;
    private:
        /**
         * Constructor hidden because is a singleton.
         * TODO change constructor so it loads information from yaml file
         */
        Config();
        Config(Config &copy) = delete;
        Config(Config &&other) = delete;
        Config &operator=(Config &copy) = delete;
        Config &operator=(Config &&other) = delete;
        // jump
        Math::Vector jumpVelocity;
        Math::Vector backflipVelocity;
        float startJumpTime{START_JUMP_TIME};
        float landTime{JUMP_LAND_TIME};
        // moving
        float walkVelocity{WALK_VELOCITY};
        // game
        uint8_t turnTime{TURN_TIME};
        float extraTurnTime{EXTRA_TURN_TIME};
        uint8_t numTeams{NUM_TEAMS};
        float gameWidth{GAME_WIDTH};
        float gameHeight{GAME_HEIGHT};
        float dyingTime{DYING_TIME};
        float drowningTime{DROWNING_TIME};
        int waterLevel{WATER_LEVEL};
        uint16_t wormHealth{WORM_HEALTH};
        // weapons
        float bazookaDmg{BAZOOKA_DAMAGE};
        float bazookaDmgRadius{BAZOOKA_DAMAGE_RADIUS};
        float minAngle{MIN_ANGLE};
        float maxAngle{MAX_ANGLE};
        float angleStep{ANGLE_STEP};
        uint16_t maxShotPower{MAX_SHOT_POWER};
    };
} // namespace Game


#endif //__GAMECONFIG_H__
