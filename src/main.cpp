#include "hello.h"
#include <box2d/b2_world.h>
#include <iostream>
#include <imgui.h>
#include "../bindings/imgui_impl_glfw.h"
#include "../bindings/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fmt/format.h>

void glfwErrorCallback(int error, const char* description) {
	fmt::print("GLFW error occured. Code: {}. Description: {}\n", error, description);
}

static void CreateUI(GLFWwindow* window, const char* glslVersion = NULL) {
	ImGui::CreateContext();

	bool success;
	success = ImGui_ImplGlfw_InitForOpenGL(window, false);
	if (success == false)
	{
		printf("ImGui_ImplGlfw_InitForOpenGL failed\n");
		assert(false);
	}

	success = ImGui_ImplOpenGL3_Init(glslVersion);
	if (success == false) {
		printf("ImGui_ImplOpenGL3_Init failed\n");
		assert(false);
	}
}


int main(int, char**) {
    const char* glslVersion = NULL;

	glfwSetErrorCallback(glfwErrorCallback);


    if (not glfwInit()) {
		fmt::print("Failed to initialize GLFW\n");
		return -1;
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(400, 400, "Vehicle_evolution", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Error" << std::endl;
		fprintf(stderr, "Failed to open GLFW g_mainWindow.\n");
		glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    // glfwSetScrollCallback(g_mainWindow, ScrollCallback);
	// glfwSetWindowSizeCallback(g_mainWindow, ResizeWindowCallback);
	// glfwSetKeyCallback(g_mainWindow, KeyCallback);
	// glfwSetCharCallback(g_mainWindow, CharCallback);
	// glfwSetMouseButtonCallback(g_mainWindow, MouseButtonCallback);
	// glfwSetCursorPosCallback(g_mainWindow, MouseMotionCallback);
	// glfwSetScrollCallback(g_mainWindow, ScrollCallback);

	// Load OpenGL functions using glad
	int version = gladLoadGL();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();

    CreateUI(window, glslVersion);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // rendering our geometries

        // render your GUI
        ImGui::Begin("Demo window");
        ImGui::Button("Hello!");
        ImGui::End();

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glfwSwapBuffers(window);
    }


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    return 0;
}
