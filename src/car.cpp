/**
 * @file car.cpp
 * @author Jakub Ptasznik
 */

#include "car.h"

#include <utility>

#include "draw.h"
#include "utils.h"
#include "world.h"

/**
 * @brief Construct a new Car:: Car object
 *
 * @param world - pointer to b2World in which car will be created.
 */
Car::Car(b2World* world) : world(world) {
    int nVertices = utils::random(minVertices, maxVertices);
    std::vector<b2Vec2> vertices(nVertices);
    for (size_t i = 0; std::cmp_less(i, nVertices); ++i) {
        auto x = utils::random(minCarX, maxCarX);
        auto y = utils::random(minCarY, maxCarY);
        vertices[i].Set(x, y);
    }

    auto randWheelNumber = [=]() { return utils::random(0, nVertices - 1); };
    int wheel1Vertex = randWheelNumber();
    int wheel2Vertex = randWheelNumber();
    while (wheel1Vertex == wheel2Vertex) {
        wheel2Vertex = randWheelNumber();
    }

    auto wheel1Radius = utils::random(minWheelRadius, maxWheelRadius);
    auto wheel2Radius = utils::random(minWheelRadius, maxWheelRadius);
    configuration = {std::move(vertices), wheel1Vertex, wheel2Vertex, wheel1Radius, wheel2Radius};

    initCar();
}

/**
 * @brief Construct a new Car:: Car object
 *
 * @param world - pointer to b2World in which car will be created.
 * @param configuration - configuration from which call should be created.
 */
Car::Car(b2World* world, const Car::Configuration configuration) : configuration(configuration), world(world) {
    initCar();
}

Car::Car(Car&& other)
    : configuration(other.configuration),
      car(other.car),
      wheel1(other.wheel1),
      wheel2(other.wheel2),
      spring1(other.spring1),
      spring2(other.spring2),
      world(other.world) {
    other.car = nullptr;
    other.wheel1 = nullptr;
    other.wheel2 = nullptr;
    other.spring1 = nullptr;
    other.spring2 = nullptr;
    other.world = nullptr;
}

Car::~Car() {
    if (spring1 != nullptr) world->DestroyJoint(spring1);
    if (spring2 != nullptr) world->DestroyJoint(spring2);

    if (wheel1 != nullptr) world->DestroyBody(wheel1);
    if (wheel2 != nullptr) world->DestroyBody(wheel2);

    if (car != nullptr) world->DestroyBody(car);
}

Car& Car::operator=(Car&& other) {
    if (this == &other) {
        return *this;
    }
    std::swap(configuration, other.configuration);
    std::swap(car, other.car);
    std::swap(wheel1, other.wheel1);
    std::swap(wheel2, other.wheel2);
    std::swap(spring1, other.spring1);
    std::swap(spring2, other.spring2);
    std::swap(world, other.world);
    return *this;
}

/**
 * @brief Get the distance from the starting point.
 *
 * @return Distance
 */
auto Car::getDistance() const -> Distance {
    return car->GetPosition().x;
}

/**
 * @brief Get configuration of the car.
 *
 * @return Configuration
 */
auto Car::getConfiguration() const -> Configuration {
    return configuration;
}

void Car::initCar() {
    // main body
    b2PolygonShape chassis;
    auto nVertices = configuration.vertices.size();
    chassis.Set(configuration.vertices.data(), nVertices);

    b2FixtureDef carFD;
    carFD.shape = &chassis;
    carFD.density = carDensity;
    carFD.filter.categoryBits = carMask;
    carFD.filter.maskBits = World::groundMask;

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(carStartX, carStartY);
    car = world->CreateBody(&bd);
    car->CreateFixture(&carFD);

    b2Vec2 wheel1Vec = configuration.vertices[configuration.wheel1Vertex];
    b2Vec2 wheel2Vec = configuration.vertices[configuration.wheel2Vertex];

    // wheels
    b2CircleShape circle1;
    circle1.m_radius = configuration.wheel1Radius;

    b2CircleShape circle2;
    circle2.m_radius = configuration.wheel2Radius;

    b2FixtureDef circleFD;
    circleFD.density = wheelDensity;
    circleFD.friction = wheelFriction;
    circleFD.filter.categoryBits = carMask;
    circleFD.filter.maskBits = World::groundMask;

    circleFD.shape = &circle1;
    bd.position.Set(wheel1Vec.x, wheel1Vec.y);
    wheel1 = world->CreateBody(&bd);
    wheel1->CreateFixture(&circleFD);

    circleFD.shape = &circle2;
    bd.position.Set(wheel2Vec.x, wheel2Vec.y);
    wheel2 = world->CreateBody(&bd);
    wheel2->CreateFixture(&circleFD);

    // joints connecting wheels with main body
    b2WheelJointDef jd;
    b2Vec2 axis(worldAxisX, worldAxisY);

    float mass1 = wheel1->GetMass();
    float mass2 = wheel2->GetMass();

    jd.Initialize(car, wheel1, wheel1->GetPosition(), axis);
    initJoint(jd, mass1);
    spring1 = static_cast<b2WheelJoint*>(world->CreateJoint(&jd));

    jd.Initialize(car, wheel2, wheel2->GetPosition(), axis);
    initJoint(jd, mass2);
    spring2 = static_cast<b2WheelJoint*>(world->CreateJoint(&jd));

    spring1->SetMotorSpeed(motorSpeed);
}

void Car::initJoint(b2WheelJointDef& jd, float mass) const {
    jd.maxMotorTorque = maxSpringMotorTorque;
    jd.enableMotor = true;
    jd.stiffness = mass * springOmega * springOmega;
    jd.damping = mass * springDampingRatio * springOmega;
    jd.lowerTranslation = springLowerTranslation;
    jd.upperTranslation = springUpperTranslation;
    jd.enableLimit = true;
}
