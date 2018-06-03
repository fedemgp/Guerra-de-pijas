/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 01/06/18
 */

#include "Config.h"
/**
 * Meyer's singleton implementation.
 * @return
 */
Game::Config &Game::Config::getInstance(){
    static Config instance;
    return instance;
}

Game::Config::Config(): jumpVelocity(JUMP_VEL_X, JUMP_VEL_Y),
                        backflipVelocity(BACKFLIP_VEL_X, BACKFLIP_VEL_Y){

}

const Math::Vector Game::Config::getJumpVelocity() const{
    return this->jumpVelocity;
}

const float Game::Config::getStartJumpTime() const{
    return this->startJumpTime;
}

const float Game::Config::getLandTime() const{
    return this->landTime;
}

const Math::Vector Game::Config::getBackflipVelocity() const{
    return this->backflipVelocity;
}

const uint8_t Game::Config::getTurnTime() const{
    return this->turnTime;
}

const float Game::Config::getGameWidth() const{
    return this->gameWidth;
}

const float Game::Config::getGameHeight() const{
    return this->gameHeight;
}

const Game::Weapon::Config & Game::Config::getBazookaConfig() const{
    return this->bazooka;
}

const float Game::Config::getDyingTime() const{
    return this->dyingTime;
}

const float Game::Config::getDrowningTime() const{
    return this->drowningTime;
}

const float Game::Config::getExtraTurnTime() const{
    return this->extraTurnTime;
}

const int Game::Config::getWaterLevel() const{
    return this->waterLevel;
}

const float Game::Config::getWalkVelocity() const{
    return this->walkVelocity;
}

const uint16_t Game::Config::getWormHealth() const{
    return this->wormHealth;
}

const Game::Weapon::Config &Game::Config::getGreenGrenadeConfig() const{
    return this->greenGrenade;
}

const uint8_t Game::Config::getNumTeams() const {
    return this->numTeams;
}

const Game::Weapon::Config &Game::Config::getClusterConfig() const{
    return this->cluster;
}


