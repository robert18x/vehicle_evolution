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
            glfwPollEvents();
            // glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
            // glClear(GL_COLOR_BUFFER_BIT);

            // feed inputs to dear imgui, start new frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // render your GUI
            ImGui::Begin("Demo window");
            ImGui::Button("Hello!");
            ImGui::End();

            // Render dear imgui into screen
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // int display_w, display_h;
            // glfwGetFramebufferSize(window, &display_w, &display_h);
            // glViewport(0, 0, display_w, display_h);
            window.swapBuffers();
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
