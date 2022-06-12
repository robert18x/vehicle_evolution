/**
 * @file world.cpp
 * @author Jakub Ptasznik
 *
 */

#include "world.h"

#include "draw.h"

World::World() : world(new b2World(gravity)), car(Car(world)) {
	gravity.Set(0.0f, -9.81f);
    world->SetGravity(gravity);
    world->SetDebugDraw(&g_debugDraw);

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
    car.CenterCamera();

    world->DebugDraw();
    g_debugDraw.Flush();
}

void World::initWorld() const {
    b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = world->CreateBody(&bd);

			b2EdgeShape shape;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.0f;
			fd.friction = 0.6f;
            fd.filter.categoryBits = 0x0001;

			float hs[10] = {0.25f, 1.0f, 3.0f, 0.0f, 0.0f, -1.0f, -2.0f, -2.0f, -1.25f, 0.0f};

			float x = -40.0f, y1 = 0.0f, dx = 10.0f;

			for (int32 i = 0; i < 10; ++i)
			{
				float y2 = hs[i] - 2.0f;
				shape.SetTwoSided(b2Vec2(x, y1), b2Vec2(x + dx, y2));
				ground->CreateFixture(&fd);
				y1 = y2;
				x += dx;
			}
		}
}
