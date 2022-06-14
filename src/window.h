/**
 * @file window.h
 * @author Robert Żurawski
 *
 */

#pragma once
#include <glad/glad.h> // glad header need to be first because
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <chrono>
#include <string>

#include "evolution_algorithm.h"
#include "window_size.h"

class Window {
  public:
    explicit Window(const std::string& name, const WindowSize& windowSize, EvolutionAlgorithm::Parameters& evolutionParams, int& epochTimeInSeconds);
    Window(const Window&) = delete;
    Window(Window&&) = delete;
    ~Window();

    bool shouldClose();
    void newFrame();
    void renderFrame();

    static constexpr int frameRate = 60;
  private:
    void initGlfwWindow(const std::string& name, const WindowSize& windowSize);
    void loadOpenglFunctions();
    void createUI();
    void setWindowsSize();
    void drawOptionsSubwindow();
    static void glfwErrorCallback(int error, const char* description);

    static constexpr char* glslVersion = nullptr;

    const std::chrono::duration<double> targetFrameDuration;

    std::chrono::duration<double> frameTime;
    std::chrono::duration<double> sleepAdjust;
    std::chrono::steady_clock::time_point startFrameTimePoint;
    std::chrono::steady_clock::time_point endFrameTimePoint;
    GLFWwindow* window;
    EvolutionAlgorithm::Parameters& evolutionParams;
    int& epochTimeInSeconds;
};
