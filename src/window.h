/**
 * @file window.h
 * @author Robert Żurawski
 *
 */

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <chrono>
#include <string>

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
    void drawOptionsSubwindow();

  private:
    void initGlfwWindow(const std::string& name, const WindowSize& windowSize);
    void loadOpenglFunctions();
    void createUI();
    void setWindowsSize();
    static void glfwErrorCallback(int error, const char* description);

    static constexpr char* glslVersion = nullptr;
    static constexpr int frameRate = 60;

    const std::chrono::duration<double> targetFrameDuration;

    std::chrono::duration<double> frameTime;
    std::chrono::duration<double> sleepAdjust;
    std::chrono::steady_clock::time_point startFrameTimePoint;
    std::chrono::steady_clock::time_point endFrameTimePoint;
    GLFWwindow* window;
};
