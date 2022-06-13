/**
 * @file car.cpp
 * @author Jakub Ptasznik
 */

#include "car.h"

#include <utility>

#include "draw.h"
#include "utils.h"

Car::Car(b2World* wrld) {
    int nVertices = utils::random(3, maxVertices);
    std::vector<b2Vec2> vertices(nVertices);
    for (size_t i = 0; std::cmp_less(i, nVertices); ++i) {
        auto x = utils::random(0.f, 8.f);
        auto y = utils::random(3.f, 11.f);
        vertices[i].Set(x, y);
    }

    auto randWheelNumber = [=]() { return utils::random(0, nVertices - 1); };
    int wheel1Vertex = randWheelNumber();
    int wheel2Vertex = randWheelNumber();
    while (wheel1Vertex == wheel2Vertex) {
        wheel2Vertex = randWheelNumber();
    }

    auto wheel1Radius = utils::random(0.2f, 1.0f);
    auto wheel2Radius = utils::random(0.2f, 1.0f);
    configuration = {std::move(vertices), wheel1Vertex, wheel2Vertex, wheel1Radius, wheel2Radius};

    world = wrld;

    initCar();
}

Car::Car(b2World* wrld, Car::Configuration conf) {
    world = wrld;
    configuration = conf;

    initCar();
}

Car::Car(Car&& other) : m_car(other.m_car), m_wheel1(other.m_wheel1), m_wheel2(other.m_wheel2), m_spring1(other.m_spring1), m_spring2(other.m_spring2) {
    other.m_car = nullptr;
    other.m_wheel1 = nullptr;
    other.m_wheel2 = nullptr;
    other.m_spring1 = nullptr;
    other.m_spring2 = nullptr;
}

void Car::centerCamera() {
    g_camera.m_center.x = m_car->GetPosition().x;
}

auto Car::getDistance() const -> Distance{
    return m_car->GetPosition().x;
}

auto Car::getConfiguration() const -> Configuration {
    return configuration;
}

void Car::initCar() {
    b2PolygonShape chassis;
    auto nVertices = configuration.vertices.size();
    chassis.Set(configuration.vertices.data(), nVertices);

    b2FixtureDef carFD;
    carFD.shape = &chassis;
    carFD.density = 1.0f;
    carFD.filter.categoryBits = carMask;
    carFD.filter.maskBits = 0x0001;

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(0.0f, 1.0f);
    m_car = world->CreateBody(&bd);
    m_car->CreateFixture(&carFD);

    b2Vec2 wheel1Vec = configuration.vertices[configuration.wheel1Vertex];
    b2Vec2 wheel2Vec = configuration.vertices[configuration.wheel2Vertex];

    b2CircleShape circle1;
    circle1.m_radius = configuration.wheel1Radius;

    b2CircleShape circle2;
    circle2.m_radius = configuration.wheel2Radius;

    b2FixtureDef circleFD;
    circleFD.density = 1.0f;
    circleFD.friction = 0.9f;
    circleFD.filter.categoryBits = carMask;
    circleFD.filter.maskBits = 0x0001;

    circleFD.shape = &circle1;
    bd.position.Set(wheel1Vec.x, wheel1Vec.y);
    m_wheel1 = world->CreateBody(&bd);
    m_wheel1->CreateFixture(&circleFD);

    circleFD.shape = &circle2;
    bd.position.Set(wheel2Vec.x, wheel2Vec.y);
    m_wheel2 = world->CreateBody(&bd);
    m_wheel2->CreateFixture(&circleFD);

    b2WheelJointDef jd;
    b2Vec2 axis(0.0f, 1.0f);

    float mass1 = m_wheel1->GetMass();
    float mass2 = m_wheel2->GetMass();

    float hertz = 4.0f;
    float dampingRatio = 0.7f;
    float omega = 2.0f * b2_pi * hertz;

    jd.Initialize(m_car, m_wheel1, m_wheel1->GetPosition(), axis);
    jd.motorSpeed = 0.0f;
    jd.maxMotorTorque = 20.0f;
    jd.enableMotor = true;
    jd.stiffness = mass1 * omega * omega;
    jd.damping = 2.0f * mass1 * dampingRatio * omega;
    jd.lowerTranslation = -0.25f;
    jd.upperTranslation = 0.25f;
    jd.enableLimit = true;
    m_spring1 = static_cast<b2WheelJoint*>(world->CreateJoint(&jd));

    jd.Initialize(m_car, m_wheel2, m_wheel2->GetPosition(), axis);
    jd.motorSpeed = 0.0f;
    jd.maxMotorTorque = 10.0f;
    jd.enableMotor = false;
    jd.stiffness = mass2 * omega * omega;
    jd.damping = 2.0f * mass2 * dampingRatio * omega;
    jd.lowerTranslation = -0.25f;
    jd.upperTranslation = 0.25f;
    jd.enableLimit = true;
    m_spring2 = static_cast<b2WheelJoint*>(world->CreateJoint(&jd));

    m_spring1->SetMotorSpeed(-25.0f);
}
