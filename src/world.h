/**
 * @file world.h
 * @author Jakub Ptasznik
 *
 */

#pragma once
#include <box2d/box2d.h>

#include <memory>
#include <vector>

#include "car.h"

class World {
  public:
    World();
    World(const World&) = delete;
    World(World&&) = delete;
    ~World();

    void step() const;

  private:
    void initWorld() const;

    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;
    b2World* world;
    b2Vec2 gravity;
    std::vector<Car> cars;
};
