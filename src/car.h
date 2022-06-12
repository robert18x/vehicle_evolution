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
        int nVertices;
        std::vector<b2Vec2> vertices;
        int wheel1Vertex;
        int wheel2Vertex;
    };

    Car(b2World* wrld);
    Car(b2World* wrld, Configuration conf);
    Car(const Car&) = delete;
    Car(Car&& other);
    ~Car();

    void CenterCamera() const;

    Configuration getConfiguration();

  private:
    b2Body* m_car;
    b2Body* m_wheel1;
    b2Body* m_wheel2;
    b2WheelJoint* m_spring1;
    b2WheelJoint* m_spring2;

    static constexpr auto carMask = 0x0004;
    static constexpr auto maxVertices = 10;
    Configuration configuration;

    b2World* world;

    void initCar();
};
