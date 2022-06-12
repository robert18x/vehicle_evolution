/**
 * @file world.cpp
 * @author Jakub Ptasznik
 *
 */

#include "world.h"

#include <random>
#include "draw.h"

World::World() : world(new b2World(gravity)) {
	gravity.Set(0.0f, -9.81f);
    world->SetGravity(gravity);
    world->SetDebugDraw(&g_debugDraw);
    int nCars = 5;
    cars.reserve(nCars);
    for (int i = 0; i < nCars; ++i) {
        cars.emplace_back(world);
    }
    g_debugDraw.Create();

    initWorld();
}

World::~World() {
    delete world;
    world = NULL;
    g_debugDraw.Destroy();
}

void World::step() const {
    uint32 flags = 0;
	flags += true * b2Draw::e_shapeBit;
	g_debugDraw.SetFlags(flags);

    world->SetAllowSleeping(true);
	world->SetWarmStarting(true);
	world->SetContinuousPhysics(true);

    world->Step(timeStep, velocityIterations, positionIterations);
    cars[0].CenterCamera();

    world->DebugDraw();
    g_debugDraw.Flush();
}

void World::initWorld() const {
    b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = world->CreateBody(&bd);

			b2EdgeShape shape;

			b2FixtureDef groundFD;
			groundFD.shape = &shape;
			groundFD.density = 0.0f;
			groundFD.friction = 0.6f;
            groundFD.filter.categoryBits = 0x0001;

            std::mt19937 gen(0);
            std::uniform_real_distribution<> dis(-3.0, 4.0);
            float hs[100];
			for (int n = 0; n < 100; ++n)
            {
                hs[n] = dis(gen);
            }

			float x = -40.0f, y1 = 0.0f, dx = 8.0f;

			for (int32 i = 0; i < 100; ++i)
			{
				float y2 = hs[i] - 2.0f;
				shape.SetTwoSided(b2Vec2(x, y1), b2Vec2(x + dx, y2));
				ground->CreateFixture(&groundFD);
				y1 = y2;
				x += dx;
			}
		}
}
