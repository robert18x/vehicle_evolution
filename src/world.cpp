/**
 * @file world.cpp
 * @author Jakub Ptasznik
 *
 */

#include "world.h"

#include <algorithm>
#include <array>
#include <functional>

#include "draw.h"
#include "utils.h"

/**
 * @brief Construct a new World:: World object
 *
 * @param nCars - how many cars should be created in the world.
 */
World::World(std::size_t nCars) : world(new b2World(gravity)) {
    gravity.Set(0.0f, -9.81f);
    world->SetGravity(gravity);
    world->SetDebugDraw(&g_debugDraw);
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

/**
 * @brief Create random path on which vehicles will ride on.
 *
 */
void World::initWorld() {
    b2Body* ground = nullptr;
    b2BodyDef bd;
    ground = world->CreateBody(&bd);

    b2EdgeShape shape;

    b2FixtureDef groundFD;
    groundFD.shape = &shape;
    groundFD.density = groundDensity;
    groundFD.friction = groundFriction;
    groundFD.filter.categoryBits = groundMask;

    std::array<float, groundSegments> hs;
    for (std::size_t n = 0; n < hs.size(); ++n) {
        hs[n] = utils::random(groundLowPoint, groundHighPoint);
    }

    float x = groundStartX, y1 = groundStartY, dx = groundSegmentLength;

    for (std::size_t i = 0; i < groundSegments; ++i) {
        float y2 = hs[i];
        shape.SetTwoSided(b2Vec2(x, y1), b2Vec2(x + dx, y2));
        ground->CreateFixture(&groundFD);
        y1 = y2;
        x += dx;
    }
}

/**
 * @brief Move everything by one step and draw updated world.
 *
 */
void World::step() {
    uint32 flags = 0;
    flags += true * b2Draw::e_shapeBit;
    g_debugDraw.SetFlags(flags);

    world->SetAllowSleeping(true);
    world->SetWarmStarting(true);
    world->SetContinuousPhysics(true);

    world->Step(timeStep, velocityIterations, positionIterations);

    auto bestCar = std::ranges::max_element(cars, {}, [](const Car& car) { return car.getDistance(); });
    g_camera.m_center.x = std::max(g_camera.m_center.x, bestCar->getDistance());  // camera is moving only forward

    world->DebugDraw();
    g_debugDraw.Flush();
}

/**
 * @brief Get all necessary information about the cars.
 *
 * @return std::vector<std::pair<Car::Distance, Car::Configuration>>
 */
std::vector<std::pair<Car::Distance, Car::Configuration>> World::getCarData() {
    std::vector<std::pair<Car::Distance, Car::Configuration>> carData;
    carData.reserve(cars.size());
    for (auto& car : cars) {
        carData.emplace_back(car.getDistance(), car.getConfiguration());
    }
    return carData;
}

/**
 * @brief Swap current cars with cars created from configurations.
 *
 * @param newCarConfigurations - configurations of cars that will be created.
 */
void World::createNewCars(const std::vector<Car::Configuration>& newCarConfigurations) {
    cars.clear();
    for (auto& carConfiguration : newCarConfigurations) {
        cars.emplace_back(world, carConfiguration);
    }
    g_camera.m_center.x = 0;  // camera position for newly created veihicles
}
