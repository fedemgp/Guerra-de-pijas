#include <iostream>

#include "Box2D/Box2D.h"
/*
 *	Testing Box2d using a small object moving across an inclined plane
 */
int main(int argc, char const *argv[]) {
	/* 
	 * define the gravity vector
	 */
	b2Vec2 gravity(0.0f, -10.0f);
	/*
	 * construct a world object, wich will holds and simulate the bodies.
	 */
	b2World world(gravity);
	//--------------------------------ground---------------------------------//
	/* 
	 * Define the inclined plane body and the position of the center mass.
	 */
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -1.0f);
	/*
	 * set the groundBody as a staticBody (it will not move during simulation)
	 */
	groundBodyDef.type = b2_staticBody;
	/* 
	 * Call to the body factory wich allocates memory for the inclined plane 
	 * body. the body is also added to the world.
	 */
	b2Body *groundBody = world.CreateBody(&groundBodyDef);
	/*
	 * Defines the vertices of the polygon, stored with a counter clockwise 
	 * winding
	 */
	b2Vec2 vertices[6];
	vertices[0].Set(10.0f,3.0f);
	vertices[1].Set(5.0f,3.0f);
	vertices[2].Set(-5.0f,1.0f);
	vertices[3].Set(-10.0f,1.0f);
	vertices[4].Set(-10.0f,-5.0f);
	vertices[5].Set(10.0f,-5.0f);
	int32 verticesQuantity = 6;
	/*
	 * Now define the ground shape, using a polygon shape
	 */
	b2PolygonShape groundShape;
	groundShape.Set(vertices, verticesQuantity);
	/*
	 * add the fixture to the ground body with a density of 0
	 */
	groundBody->CreateFixture(&groundShape, 0.0f);
	//--------------------------------ground---------------------------------//
	//---------------------------------wall----------------------------------//
	/*
	 * Define an edge shape that works as a wall limit for the ball
	 */	
	b2BodyDef wallBodyDef;
	wallBodyDef.position.Set(-10.0f, -5.0f);
	/*
	 * Set wall as a static body
	 */
	wallBodyDef.type = b2_staticBody;
	b2Body *wallBody = world.CreateBody(&wallBodyDef);
	/*
	 * define the extremes of the edge (in local coordinates)
	 */
	b2Vec2 v1(0.0f,0.0f), v2(0.0f,10.0f);
	b2EdgeShape edgeShape;
	edgeShape.Set(v1,v2);
	wallBody->CreateFixture(&edgeShape, 0.0f);
	//---------------------------------wall----------------------------------//
	//---------------------------------ball----------------------------------//
	/*
	 * Now define the dynamic body (a ball), setting its starting position
	 * and calling the body factory.
	 */
	b2BodyDef ballDef;
	ballDef.type = b2_dynamicBody;
	ballDef.position.Set(10.0f, 3.0f);
	b2Body *ballBody = world.CreateBody(&ballDef);
	/*
	 * Define a circleShape for our dynamic body
	 */
	b2CircleShape ballShape;
	/*
	 * Shape position is expresed in local coordinates (from the point of 
	 * view of the body). In our case, the ball shape will be in the local
	 * coordinates (0.0;0.0), which in the world coordinates wille be 
	 * (10; 4).
	 */
	ballShape.m_p.Set(0.0f,0.0f);
	ballShape.m_radius = 1.0f;
	/*
	 * define the dynamic ball fixture
	 */
	b2FixtureDef ballFixtureDef;
	ballFixtureDef.shape = &ballShape;
	/*
	 * setting the density to be non-zero will make the body dynamic
	 */
	ballFixtureDef.density = 1.0f;
	/*
	 * Adding some friction 
	 */
	ballFixtureDef.friction = 0.2f;
	/*
	 * Add the fixture to the body
	 */
	ballBody->CreateFixture(&ballFixtureDef);
	//---------------------------------ball----------------------------------//
	/*
	 * Prepare for simulation. Typically we use a time step of 1/60 of a
	 * second (60Hz) and 10 iterations. This provides a high quality simulation
	 * in most game scenarios.
	 */
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	/*
	 * game loop
	 */
	for (int32 i = 0; i < 240 ; i++) {
		/*
		 * Apply an initial force to the ball in the point (11; 4) 
		 * with value of (-1N, 0);
		 */
//		b2Vec2 force;
//		force.Set(-10.0f, 0.0f);
//		b2Vec2 forcePoint;
//		forcePoint.Set(11.0f, 4.0f);
//		ballBody->ApplyForce(force, forcePoint, true);
		if (i == 0) {
			b2Vec2 impulse(-10.0f, 0.0f);
			b2Vec2 impulsePoint(11.0f, 4.0f);
			ballBody->ApplyLinearImpulse(impulse, impulsePoint, true);		
		}
		/*
		 * Instruct the world to perform a single step of simulation.
		 */
		world.Step(timeStep, velocityIterations, positionIterations);
		/*
		 * Get the position and angle of the ball.
		 */
		b2Vec2 position = ballBody->GetPosition();
		float32 angle = ballBody->GetAngle();
	    printf("x: %4.2f  y: %4.2f angle: %4.2f\n", position.x, position.y, angle);
	}

	return 0;
}