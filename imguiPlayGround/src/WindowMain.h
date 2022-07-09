#pragma once

struct GLFWwindow;

class WindowMain
{
public:
	static WindowMain& getInstance();

	~WindowMain();

	void initWindowMain();

	void executeEventLoop();

private:
	WindowMain();

	GLFWwindow* glfwWindow_;
};