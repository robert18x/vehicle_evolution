/**
 * @file main.cpp
 * @author Robert Żurawski
 * @author Jakub Ptasznik
 *
 */

#include <box2d/box2d.h>

#include <iostream>
#include "draw.h"
#include "window.h"
#include "world.h"

int main(int, char**) {
    try {
        Window window("Vehicle evolution", {400, 400});
        World world;

        while (not window.shouldClose()) {
            window.newFrame();

            world.step();

            int optionsSubwindowWidth = 100;
            int optionsSubwindowHeight= 100;
            int windowMargin = 10;
            ImGui::SetNextWindowPos(ImVec2((float)g_camera.m_width - optionsSubwindowWidth - windowMargin, windowMargin));
            ImGui::SetNextWindowSize(ImVec2((float)optionsSubwindowWidth, (float)optionsSubwindowHeight - 20));
            ImGui::Begin("Params", &g_debugDraw.m_showUI, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
            ImGui::Button("Hello!");
            ImGui::End();


            // render your GUI


            window.renderFrame();
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
