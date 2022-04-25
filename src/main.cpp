#include <box2d/b2_world.h>
#include <iostream>
#include <imgui.h>
#include "../bindings/imgui_impl_glfw.h"
#include "../bindings/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fmt/format.h>
#include "window.h"


int main(int, char**) {
    try {
        Window window;
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
