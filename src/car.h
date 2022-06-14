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
    Car(b2World* world, const Configuration configuration);
    Car(const Car&) = delete;
    Car(Car&& other);
    ~Car();
    Car& operator=(const Car&) = delete;
    Car& operator=(Car&&);

    typedef float Distance;
    Distance getDistance() const;

    Configuration getConfiguration() const;

    static constexpr int maxVertices = 8;
    static constexpr int minVertices = 3;
    static constexpr double minWheelRadius = 0.2;
    static constexpr double maxWheelRadius = 1.0;
    static constexpr float minCarX = 0.0f;
    static constexpr float maxCarX = 8.0f;
    static constexpr float minCarY = 3.0f;
    static constexpr float maxCarY = 11.0f;

  private:
    void initCar();
    void initJoint(b2WheelJointDef& jd, float mass) const;

    static constexpr int carMask = 0x0004;

    Configuration configuration;
    b2Body* car;
    b2Body* wheel1;
    b2Body* wheel2;
    b2WheelJoint* spring1;
    b2WheelJoint* spring2;
    b2World* world;

    static constexpr int groundMask = 0x0001;  // Move somewhere else
    static constexpr float worldAxisX = 0.0f;
    static constexpr float worldAxisY = 1.0f;  //
    static constexpr float carDensity = 1.0f;
    static constexpr float carStartX = 0.0f;
    static constexpr float carStartY = 1.0f;
    static constexpr float wheelDensity = 1.0f;
    static constexpr float wheelFriction = 0.9f;
    static constexpr float springHertz = 4.0f;
    static constexpr float springOmega = 2.0f * b2_pi * springHertz;
    static constexpr float springDampingRatio = 0.35f;
    static constexpr float maxSpringMotorTorque = 20.0f;
    static constexpr float springLowerTranslation = -0.25f;
    static constexpr float springUpperTranslation = 0.25f;
    static constexpr float motorSpeed = -25.0f;
};
