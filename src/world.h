/**
 * @file world.h
 * @author Jakub Ptasznik
 *
 */

#pragma once
#include <box2d/box2d.h>

#include <vector>
#include <utility>

#include "car.h"

class World {
  public:
    World();
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
};
