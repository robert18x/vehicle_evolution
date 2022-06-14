/**
 * @file world.h
 * @author Jakub Ptasznik
 *
 */

#pragma once
#include <box2d/box2d.h>

#include <utility>
#include <vector>

#include "car.h"

class World {
  public:
    World(std::size_t nCars);
    World(const World&) = delete;
    World(World&&) = delete;
    ~World();

    void step();
    std::vector<std::pair<Car::Distance, Car::Configuration>> getCarData();
    void createNewCars(const std::vector<Car::Configuration>& newCarConfigurations);

  private:
    void initWorld();

    std::vector<Car> cars;
    b2Vec2 gravity;
    b2World* world;
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    static constexpr float groundDensity = 0.0f;
    static constexpr float groundFriction = 0.6f;
    static constexpr int groundMask = 0x0001;
    static constexpr int groundSegments = 100;
    static constexpr float groundLowPoint = -5.0f;
    static constexpr float groundHighPoint = 2.0f;
    static constexpr float groundStartX = -40.0f;
    static constexpr float groundStartY = 0.0f;
    static constexpr float groundSegmentLength = 8.0f;
};
