/**
 * @file car.cpp
 * @author Jakub Ptasznik
 */

#include "car.h"

#include <random>

#include "draw.h"

Car::Car(b2World* wrld) {
    static std::mt19937 gen(0);
    static std::uniform_int_distribution<> disVertices(3, 10);
    static std::uniform_real_distribution<> dis(0.0, 8.0);

    int nVertices = disVertices(gen);
    std::vector<b2Vec2> vertices;
    vertices.reserve(maxVertices);
    for (int i = 0; i < nVertices; ++i) {
        double x = dis(gen);
        double y = dis(gen);
        vertices[i].Set(x, y);
    }

    static std::uniform_int_distribution<> disWheel(0, nVertices - 1);
    int wheel1Vertex = disWheel(gen);
    int wheel2Vertex = wheel1Vertex;
    while (wheel1Vertex == wheel2Vertex) {
        wheel2Vertex = disWheel(gen);
    }

    configuration = {nVertices, std::move(vertices), wheel1Vertex, wheel2Vertex};

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

Car::~Car() {
    world->DestroyJoint(m_spring1);
    world->DestroyJoint(m_spring2);

    world->DestroyBody(m_wheel1);
    world->DestroyBody(m_wheel2);
    world->DestroyBody(m_car);
}

void Car::CenterCamera() const {
    g_camera.m_center.x = m_car->GetPosition().x;
}

auto Car::getConfiguration() -> Configuration {
    return configuration;
}

void Car::initCar() {
    b2PolygonShape chassis;
    chassis.Set(configuration.vertices.data(), configuration.nVertices);

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

    b2CircleShape circle;
    circle.m_radius = 0.4f;

    b2FixtureDef fd;
    fd.shape = &circle;
    fd.density = 1.0f;
    fd.friction = 0.9f;
    fd.filter.categoryBits = carMask;
    fd.filter.maskBits = 0x0001;

    bd.position.Set(wheel1Vec.x, wheel1Vec.y);
    m_wheel1 = world->CreateBody(&bd);
    m_wheel1->CreateFixture(&fd);

    bd.position.Set(wheel2Vec.x, wheel2Vec.y);
    m_wheel2 = world->CreateBody(&bd);
    m_wheel2->CreateFixture(&fd);

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
    m_spring1 = (b2WheelJoint*)world->CreateJoint(&jd);

    jd.Initialize(m_car, m_wheel2, m_wheel2->GetPosition(), axis);
    jd.motorSpeed = 0.0f;
    jd.maxMotorTorque = 10.0f;
    jd.enableMotor = false;
    jd.stiffness = mass2 * omega * omega;
    jd.damping = 2.0f * mass2 * dampingRatio * omega;
    jd.lowerTranslation = -0.25f;
    jd.upperTranslation = 0.25f;
    jd.enableLimit = true;
    m_spring2 = (b2WheelJoint*)world->CreateJoint(&jd);

    m_spring1->SetMotorSpeed(-25.0f);
}
