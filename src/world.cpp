/**
 * @file world.cpp
 * @author Jakub Ptasznik
 *
 */

#include "world.h"

#include "draw.h"

World::World() {
	gravity.Set(0.0f, -10.0f);
	world = new b2World(gravity);

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

    world->DebugDraw();
    g_debugDraw.Flush();
}

void World::initWorld() const {
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 5.0f);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 20.0f);
    b2Body* body = world->CreateBody(&bodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(20.0f, 3.0f);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    groundBody->CreateFixture(&groundBox, 0.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
}
