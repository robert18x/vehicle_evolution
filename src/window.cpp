/**
 * @file window.cpp
 * @author Robert Żurawski
 *
 */

#include "window.h"

#include <box2d/box2d.h>
#include <fmt/format.h>

#include <chrono>
#include <stdexcept>
#include <thread>

#include "config.h"
#include "draw.h"
#ifdef _WIN32
#include "../out/build/bindings/imgui_impl_glfw.h"
#include "../out/build/bindings/imgui_impl_opengl3.h"
#else
#include "../bindings/imgui_impl_glfw.h"
#include "../bindings/imgui_impl_opengl3.h"
#endif

Window::Window(const std::string& name, const WindowSize& windowSize)
    : targetFrameDuration(1.0 / static_cast<double>(frameRate)), frameTime(0.0), sleepAdjust(0.0) {
    initGlfwWindow(name, windowSize);
    loadOpenglFunctions();
    createUI();
    ImGui::StyleColorsClassic();
}

Window::~Window() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    glfwTerminate();
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
    glfwSetMouseButtonCallback(window, ImGui_ImplGlfw_MouseButtonCallback);
}

void Window::loadOpenglFunctions() {
    // Load OpenGL functions using glad
    gladLoadGL();
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
    glfwPollEvents();
    endFrameTimePoint = std::chrono::steady_clock::now();
    std::chrono::duration<double> timeUsed = endFrameTimePoint - startFrameTimePoint;
    std::chrono::duration<double> sleepTime = targetFrameDuration - timeUsed + sleepAdjust;
    if (sleepTime > std::chrono::duration<double>(0)) {
        std::this_thread::sleep_for(sleepTime);
    }
    frameTime = std::chrono::steady_clock::now() - startFrameTimePoint;
    // Compute the sleep adjustment using a low pass filter
    sleepAdjust = 0.9 * sleepAdjust + 0.1 * (targetFrameDuration - frameTime);
}

void Window::newFrame() {
    startFrameTimePoint = std::chrono::steady_clock::now();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
