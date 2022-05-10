#include "window.h"

#include <fmt/format.h>

#include <stdexcept>

#include "../bindings/imgui_impl_glfw.h"
#include "../bindings/imgui_impl_opengl3.h"

Window::Window(const std::string& name, const WindowSize& windowSize) {
    initGlfwWindow(name, windowSize);
    createUI();
    ImGui::StyleColorsClassic();
}

Window::~Window() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Window::initGlfwWindow(const std::string& name, const WindowSize& windowSize) {
    glfwSetErrorCallback(Window::glfwErrorCallback);

    auto status = glfwInit();
    if (status != GLFW_TRUE) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowSize.width, windowSize.height, name.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to open GLFW window.");
    }
    glfwMakeContextCurrent(window);
}

void Window::createUI() {
    ImGui::CreateContext();

    bool success = ImGui_ImplGlfw_InitForOpenGL(window, false);
    if (success == false) {
        throw std::runtime_error("ImGui_ImplGlfw_InitForOpenGL failed\n");
    }

    success = ImGui_ImplOpenGL3_Init(glslVersion);
    if (success == false) {
        throw std::runtime_error("ImGui_ImplOpenGL3_Init failed\n");
    }
}

void Window::glfwErrorCallback(int error, const char* description) {
    fmt::print("GLFW error occured. Code: {}. Description: {}\n", error, description);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::renderFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
}

void Window::newFrame() {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
