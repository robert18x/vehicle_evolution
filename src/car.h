/**
 * @file car.h
 * @author Jakub Ptasznik
 */

#pragma once
#include <box2d/box2d.h>

class Car {
  public:
    Car(b2World* world);
    Car(const Car&) = delete;
    Car(Car&& other);
    void RandomCar();
    void CenterCamera() const;

  private:
    b2Body* m_car;
    b2Body* m_wheel1;
    b2Body* m_wheel2;

    b2WheelJoint* m_spring1;
    b2WheelJoint* m_spring2;
    static constexpr auto carMask = 0x0004;
};
