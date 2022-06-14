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

#include "draw.h"
#include "utils.h"
#ifdef _WIN32
#include "../out/build/bindings/imgui_impl_glfw.h"
#include "../out/build/bindings/imgui_impl_opengl3.h"
#else
#include "../bindings/imgui_impl_glfw.h"
#include "../bindings/imgui_impl_opengl3.h"
#endif

/**
 * @brief Construct a new Window:: Window object
 *
 * @param name - name of the window.
 * @param windowSize - size of the window.
 * @param evolutionParams - initial parameters of evolution algorithm.
 * @param epochTimeInSeconds - how many seconds each epoch will last.
 */
Window::Window(const std::string& name, const WindowSize& windowSize, EvolutionAlgorithm::Parameters& evolutionParams, int& epochTimeInSeconds)
    : targetFrameDuration(1.0 / static_cast<double>(frameRate)),
      frameTime(0.0),
      sleepAdjust(0.0),
      evolutionParams(evolutionParams),
      epochTimeInSeconds(epochTimeInSeconds) {
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
    glfwSetKeyCallback(window, ImGui_ImplGlfw_KeyCallback);
    glfwSetCharCallback(window, ImGui_ImplGlfw_CharCallback);
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
    throw std::runtime_error(fmt::format("GLFW error occured. Code: {}. Description: {}\n", error, description));
}

/**
 * @brief Tells if window should close or not.
 *
 * @return true
 * @return false
 */
bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

/**
 * @brief Render new frame for the window.
 *
 */
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

/**
 * @brief Create new clear frame for the window.
 *
 */
void Window::newFrame() {
    startFrameTimePoint = std::chrono::steady_clock::now();
    setWindowsSize();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    drawOptionsSubwindow();
}

void Window::drawOptionsSubwindow() {
    static constexpr float subwindowWidth = 300.f;
    static constexpr float subwindowHeight = 150.f;
    static constexpr float windowMargin = 10.f;
    auto inputFormat = "%.2f";
    ImGui::SetNextWindowPos(ImVec2(static_cast<float>(g_camera.m_width) - subwindowWidth - windowMargin, windowMargin));
    ImGui::SetNextWindowSize(ImVec2(subwindowWidth, subwindowHeight - windowMargin));
    ImGui::Begin("Params", &g_debugDraw.m_showUI, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::InputDouble("crossover prob", &evolutionParams.crossoverProbability, 0.01, 0.02, inputFormat);
    ImGui::InputDouble("mutation prob", &evolutionParams.mutationProbability, 0.01, 0.02, inputFormat);
    ImGui::InputDouble("mutation rate", &evolutionParams.mutationRate, 0.01, 0.02, inputFormat);
    ImGui::InputInt("epoch time", &epochTimeInSeconds);
    ImGui::End();

    evolutionParams.crossoverProbability = utils::getValueFromRange(0.0, evolutionParams.crossoverProbability, 1.0);
    evolutionParams.crossoverProbability = utils::getValueFromRange(0.0, evolutionParams.crossoverProbability, 1.0);
    evolutionParams.mutationRate = utils::getValueFromRange(0.0, evolutionParams.mutationRate, 5.0);
    epochTimeInSeconds = std::max(0, epochTimeInSeconds);
}

void Window::setWindowsSize() {
    glfwGetWindowSize(window, &g_camera.m_width, &g_camera.m_height);

    int bufferWidth = 0;
    int bufferHeight = 0;
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
    glViewport(0, 0, bufferWidth, bufferHeight);
}
