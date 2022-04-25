#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "../bindings/imgui_impl_glfw.h"
#include "../bindings/imgui_impl_opengl3.h"

class Window {
  public:
    explicit Window();
    Window(const Window&) = delete;
    Window(Window&&) = delete;
    ~Window();

    bool shouldClose();
    void swapBuffers();

  private:
    void initGlfwWindow();
    void CreateUI();
    static void glfwErrorCallback(int error, const char* description);

    static constexpr char* glslVersion = nullptr;
    GLFWwindow* window;
};
