#include <box2d/box2d.h>

#include <iostream>

#include "window.h"
#include "draw.h"

int main(int, char**) {
    try {
        Window window("Vehicle evolution", {400, 400});

        // Setting up a world
        b2Vec2 gravity;
	    gravity.Set(0.0f, -10.0f);
	    b2World world = b2World(gravity);

        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(0.0f, 5.0f);
        b2Body* groundBody = world.CreateBody(&groundBodyDef);

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(0.0f, 20.0f);
        b2Body* body = world.CreateBody(&bodyDef);

        b2PolygonShape groundBox;
        groundBox.SetAsBox(20.0f, 3.0f);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(1.0f, 1.0f);

        groundBody->CreateFixture(&groundBox, 0.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        body->CreateFixture(&fixtureDef);

        world.SetDebugDraw(&g_debugDraw);

        g_debugDraw.Create();

        while (not window.shouldClose()) {
            window.newFrame();

            // world Step
            float timeStep = 1.0f / 60.0f;
            int32 velocityIterations = 8;
            int32 positionIterations = 3;

            uint32 flags = 0;
	        flags += true * b2Draw::e_shapeBit;
	        g_debugDraw.SetFlags(flags);

            world.SetAllowSleeping(true);
	        world.SetWarmStarting(true);
	        world.SetContinuousPhysics(true);

            world.Step(timeStep, velocityIterations, positionIterations);

	        world.DebugDraw();
            g_debugDraw.Flush();

            // render your GUI
            ImGui::Begin("Demo window");
            ImGui::Button("Hello!");
            ImGui::End();

            window.renderFrame();
        }
        g_debugDraw.Destroy();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
