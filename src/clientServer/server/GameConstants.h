/*
 *  Created by Federico Manuel Gomez Peter.
 *  date: 01/06/18
 */

#ifndef __GAMECONSTANTS_H__
#define __GAMECONSTANTS_H__
// Jumping
#define START_JUMP_TIME 0.6f
#define JUMP_LAND_TIME 0.3f
#define JUMP_VEL_X 2.0f
#define JUMP_VEL_Y 6.0f
#define BACKFLIP_VEL_X (-1.2f)
#define BACKFLIP_VEL_Y 9.4f
// Moving
#define WALK_VELOCITY 3.0f
// Stage and general game config
#define TURN_TIME 10
#define EXTRA_TURN_TIME 3
#define NUM_TEAMS 2
#define GAME_HEIGHT 30.0f
#define GAME_WIDTH 30.0f
#define DYING_TIME 2.6f
#define DROWNING_TIME 2.6f
#define WATER_LEVEL (-2)
#define WORM_HEALTH 100
// Weapons
//Bazooka
#define BAZOOKA_DAMAGE 50
#define BAZOOKA_DAMAGE_RADIUS 2.0f
#define BAZOOKA_MIN_ANGLE -90
#define BAZOOKA_MAX_ANGLE 84.375f
//Grenade
#define GRENADE_DAMAGE 30
#define GRENADE_RADIUS 2.0f
#define GRENADE_MIN_ANGLE -84.375f
#define GRENADE_MAX_ANGLE 90
//Cluster
#define CLUSTER_DAMAGE 30
#define CLUSTER_RADIUS 2.0f
#define CLUSTER_MIN_ANGLE -84.375f
#define CLUSTER_MAX_ANGLE 90

#define ANGLE_STEP 5.625f
#define MAX_SHOT_POWER 50


#endif //__GAMECONSTANTS_H__
