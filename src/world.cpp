/**
 * @file world.cpp
 * @author Jakub Ptasznik
 *
 */

#include "world.h"

#include "draw.h"

World::World() {
	gravity.Set(0.0f, -2.0f);
	world = new b2World(gravity);

    world->SetDebugDraw(&g_debugDraw);

    g_debugDraw.Create();

    initWorld();
}

World::~World() {
    delete world;
    world = NULL;
    g_debugDraw.Destroy();
}

void World::step() const {
    uint32 flags = 0;
	flags += true * b2Draw::e_shapeBit;
	g_debugDraw.SetFlags(flags);

    world->SetAllowSleeping(true);
	world->SetWarmStarting(true);
	world->SetContinuousPhysics(true);

    world->Step(timeStep, velocityIterations, positionIterations);

    world->DebugDraw();
    g_debugDraw.Flush();
}

void World::initWorld() const {
    b2Body* ground = NULL;
		{
			b2BodyDef bd;
			ground = world->CreateBody(&bd);

			b2EdgeShape shape;

			b2FixtureDef fd;
			fd.shape = &shape;
			fd.density = 0.0f;
			fd.friction = 0.6f;

			float hs[10] = {0.25f, 1.0f, 3.0f, 0.0f, 0.0f, -1.0f, -2.0f, -2.0f, -1.25f, 0.0f};

			float x = -40.0f, y1 = 0.0f, dx = 10.0f;

			for (int32 i = 0; i < 10; ++i)
			{
				float y2 = hs[i] - 2.0f;
				shape.SetTwoSided(b2Vec2(x, y1), b2Vec2(x + dx, y2));
				ground->CreateFixture(&fd);
				y1 = y2;
				x += dx;
			}
		}

    b2Body* m_car;
	b2Body* m_wheel1;
	b2Body* m_wheel2;

    b2WheelJoint* m_spring1;
	b2WheelJoint* m_spring2;

    {
		b2PolygonShape chassis;
		b2Vec2 vertices[8];
		vertices[0].Set(-1.5f, -0.5f);
		vertices[1].Set(1.5f, -0.5f);
		vertices[2].Set(1.5f, 0.0f);
		vertices[3].Set(0.0f, 0.9f);
		vertices[4].Set(-1.15f, 0.9f);
		vertices[5].Set(-1.5f, 0.2f);
		chassis.Set(vertices, 6);

		b2CircleShape circle;
		circle.m_radius = 0.4f;

		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(0.0f, 1.0f);
		m_car = world->CreateBody(&bd);
		m_car->CreateFixture(&chassis, 1.0f);

		b2FixtureDef fd;
		fd.shape = &circle;
		fd.density = 1.0f;
		fd.friction = 0.9f;

		bd.position.Set(-1.0f, 0.35f);
		m_wheel1 = world->CreateBody(&bd);
		m_wheel1->CreateFixture(&fd);

		bd.position.Set(1.0f, 0.4f);
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
		}

    m_spring1->SetMotorSpeed(-10.0f);
    g_camera.m_center.x = m_car->GetPosition().x;
}
