#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

int main()
{
	if (glfwInit() == GL_FALSE)
	{
		std::cerr << "Failed to init GLFW!!" << std::endl;
		return 1;
	}

	std::atexit(glfwTerminate);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* const window(glfwCreateWindow(640, 480, "Hello!", nullptr, nullptr));
	if (window == nullptr)
	{
		std::cerr << "Failed to create window!!" << std::endl;
		return 1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to init glew!!" << std::endl;
		return 1;
	}

	glfwSwapInterval(1);

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	while (glfwWindowShouldClose(window) == GL_FALSE)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	return 0;
}