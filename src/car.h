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
    Car(b2World* world, Configuration conf);
    Car(const Car&) = delete;
    Car(Car&& other);
    ~Car();
    Car& operator=(const Car&) = delete;
    Car& operator=(Car&&);

    void centerCamera() const;
    typedef double Distance;
    Distance getDistance() const;

    Configuration getConfiguration() const;
    static constexpr auto maxVertices = 8;

  private:
    void initCar();
    static constexpr auto carMask = 0x0004;

    Configuration configuration;

    b2Body* m_car;
    b2Body* m_wheel1;
    b2Body* m_wheel2;
    b2WheelJoint* m_spring1;
    b2WheelJoint* m_spring2;

    b2World* world;
};
