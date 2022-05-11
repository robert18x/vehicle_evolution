#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
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



  private:
    void initGlfwWindow(const std::string& name, const WindowSize& windowSize);
    void createUI();
    static void glfwErrorCallback(int error, const char* description);

    static constexpr char* glslVersion = nullptr;
    GLFWwindow* window;
};
