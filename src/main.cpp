/**
 * @file main.cpp
 * @author Robert Żurawski
 * @author Jakub Ptasznik
 *
 */

#include <box2d/box2d.h>

#include <iostream>

#include "window.h"
#include "world.h"

int main(int, char**) {
    try {
        Window window("Vehicle evolution", {400, 400});
        World world;

        while (not window.shouldClose()) {
            window.newFrame();

            world.step();

            // render your GUI
            ImGui::Begin("Demo window");
            ImGui::Button("Hello!");
            ImGui::End();

            window.renderFrame();
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
