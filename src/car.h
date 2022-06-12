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
        int nVertces;
        std::vector<b2Vec2> vertices;
    };

    Car(b2World* world);
    Car(b2World* world, Configuration configuration);
    Car(const Car&) = delete;
    Car(Car&& other);

    void RandomCar(b2World* world);
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
};
