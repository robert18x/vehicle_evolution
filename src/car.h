/**
 * @file car.h
 * @author Jakub Ptasznik
 */

#pragma once
#include <box2d/box2d.h>

#include <vector>

class Car {
  public:
    struct Configuration {
        std::vector<b2Vec2> vertices;
        int wheel1Vertex;
        int wheel2Vertex;
        double wheel1Radius;
        double wheel2Radius;
    };

    Car(b2World* world);
    Car(b2World* world, Configuration configuration);
    Car(const Car&) = delete;
    Car(Car&& other);
    ~Car();
    Car& operator=(const Car&) = delete;
    Car& operator=(Car&&);

    typedef float Distance;
    Distance getDistance() const;

    Configuration getConfiguration() const;

    static constexpr int maxVertices = 8;
    static constexpr double minWheelRadius = 0.2;
    static constexpr double maxWheelRadius = 1.0;

  private:
    void initCar();

    static constexpr int carMask = 0x0004;

    Configuration configuration;
    b2Body* car;
    b2Body* wheel1;
    b2Body* wheel2;
    b2WheelJoint* spring1;
    b2WheelJoint* spring2;
    b2World* world;
};
