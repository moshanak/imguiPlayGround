#pragma once

struct GLFWwindow;

class WindowMain
{
public:
	static WindowMain& getInstance();

	~WindowMain();

	void initWindowMain();

	void executeEventLoop();

	const int& getWidth() const { return width_; }
	const int& getHeight() const { return height_; }

private:
	WindowMain();

	GLFWwindow* glfwWindow_;
	int width_;
	int height_;
};