/**
 * @file world.cpp
 * @author Jakub Ptasznik
 *
 */

#include "world.h"

#include <array>
#include <algorithm>
#include <functional>
#include "draw.h"
#include "utils.h"

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
    cars.clear();
    delete world;
    world = nullptr;
    g_debugDraw.Destroy();
}

void World::step() {
    uint32 flags = 0;
    flags += true * b2Draw::e_shapeBit;
    g_debugDraw.SetFlags(flags);

    world->SetAllowSleeping(true);
    world->SetWarmStarting(true);
    world->SetContinuousPhysics(true);

    world->Step(timeStep, velocityIterations, positionIterations);

    auto bestCar = std::ranges::max_element(cars, {}, [](const Car& car) { return car.getDistance(); });
    bestCar->centerCamera();

    world->DebugDraw();
    g_debugDraw.Flush();
}

void World::initWorld() {
    b2Body* ground = nullptr;
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

std::vector<std::pair<Car::Distance, Car::Configuration>> World::getCarData() {
    std::vector<std::pair<Car::Distance, Car::Configuration>> carData;
    carData.reserve(cars.size());
    for (auto& car : cars) {
        carData.emplace_back(car.getDistance(), car.getConfiguration());
    }
    return carData;
}
