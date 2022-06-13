/**
 * @file world.cpp
 * @author Jakub Ptasznik
 *
 */

#include "world.h"
#include <array>
#include "utils.h"
#include "draw.h"

World::World() : world(new b2World(gravity)) {
    gravity.Set(0.0f, -9.81f);
    world->SetGravity(gravity);
    world->SetDebugDraw(&g_debugDraw);
    std::size_t nCars = 5;
    cars.reserve(nCars);
    for (std::size_t i = 0; i < nCars; ++i) {
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

        std::array<float, 100> hs;
        for (std::size_t n = 0; n < hs.size(); ++n) {
            hs[n] = utils::random(-5.0f, 2.0f);
        }

        float x = -40.0f, y1 = 0.0f, dx = 8.0f;

        for (std::size_t i = 0; i < 100; ++i) {
            float y2 = hs[i];
            shape.SetTwoSided(b2Vec2(x, y1), b2Vec2(x + dx, y2));
            ground->CreateFixture(&groundFD);
            y1 = y2;
            x += dx;
        }
    }
}
