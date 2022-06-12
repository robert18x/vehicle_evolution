/**
 * @file window.h
 * @author Robert Żurawski
 *
 */

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <string>
#include <chrono>
#include "window_size.h"

class Window {
  public:
    explicit Window(const std::string& name, const WindowSize& windowSize);
    Window(const Window&) = delete;
    Window(Window&&) = delete;
    ~Window();

    bool shouldClose();
    void newFrame();
    void renderFrame();

  private:
    void initGlfwWindow(const std::string& name, const WindowSize& windowSize);
    void loadOpenglFunctions();
    void createUI();
    static void glfwErrorCallback(int error, const char* description);

    static constexpr char* glslVersion = nullptr;
    const std::chrono::duration<double> targetFrameDuration;

    std::chrono::duration<double> frameTime;
    std::chrono::duration<double> sleepAdjust;
    std::chrono::steady_clock::time_point startFrameTimePoint;
    std::chrono::steady_clock::time_point endFrameTimePoint;
    GLFWwindow* window;
};
