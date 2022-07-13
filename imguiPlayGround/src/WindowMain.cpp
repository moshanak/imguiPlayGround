#include "WindowMain.h"
#include "GLSLManager.h"
#include "Scene.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <iostream>

void GLAPIENTRY messageCallback(
	GLenum source,
	GLenum type,
	GLuint /* id*/,
	GLenum severity,
	GLsizei /*length*/,
	const GLchar* message,
	const void* /*userParam*/)
{
	std::cout << "GL CALLBACK: " << source << " type = " << type << ", severity = " << severity << ", message = " << message << std::endl;
}

WindowMain& WindowMain::getInstance()
{
	static WindowMain instance_;
	return instance_;
}

void WindowMain::initWindowMain()
{
	if (glfwInit() == GL_FALSE)
	{
		std::cerr << "Failed to init GLFW!!" << std::endl;
		exit(1);
	}

	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindow_ = glfwCreateWindow(width_, height_, "imgui playground", nullptr, nullptr);
	if (glfwWindow_ == nullptr)
	{
		std::cerr << "Failed to create window!!" << std::endl;
		exit(1);
	}

	glfwMakeContextCurrent(glfwWindow_);

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to init glew!!" << std::endl;
		exit(1);
	}
#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(messageCallback, 0);
#endif //  _DEBUG

	glfwSwapInterval(1);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// Setup Dear ImGui style
	// ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(glfwWindow_, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void WindowMain::executeEventLoop()
{
	// Our state
	bool show_demo_window = true;
	bool show_another_window = true;
	ImVec4 clear_color = ImVec4(1.00f, 0.55f, 0.60f, 1.00f);

	GLSLManager::getInstance().buildAllGLSL();

	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	scene->init();

	while (glfwWindowShouldClose(glfwWindow_) == GL_FALSE)
	{
		// wait or no wait mouse events
		// glfwWaitEvents();
		glfwPollEvents();

		glfwGetFramebufferSize(glfwWindow_, &width_, &height_);

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("setting"); // Create a window called "Hello, world!" and append into it.

			ImGui::ColorEdit3("background color", &backgroundColor_[0]); // Edit 3 floats representing a color

			ImGui::Text("This is some useful text.");		   // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f

			if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		// update input information
		{
			double x, y;
			glfwGetCursorPos(glfwWindow_, &x, &y);
			curMousePos_.x = static_cast<float>(x);
			curMousePos_.y = static_cast<float>(y);
		}

		pressMouseButtonRight_ = (glfwGetMouseButton(glfwWindow_, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
		pressMouseButtonLeft_ = (glfwGetMouseButton(glfwWindow_, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);

		// update draw actors
		scene->update();

		// Rendering
		scene->draw();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		prevMousePos_ = curMousePos_;

		glfwSwapBuffers(glfwWindow_);
	}
}

WindowMain::WindowMain()
	: width_(1920)
	, height_(1080)
	, pressMouseButtonRight_(false)
	, pressMouseButtonLeft_(false)
{
}

WindowMain::~WindowMain()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(glfwWindow_);
	glfwTerminate();
}