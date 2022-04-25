#include <box2d/b2_world.h>

#include <iostream>

#include "window.h"

int main(int, char**) {
    try {
        Window window("Vehicle evolution", {400, 400});
        while (not window.shouldClose()) {
            window.newFrame();

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
