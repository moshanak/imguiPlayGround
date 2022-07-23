#pragma once
#include <glm/glm.hpp>
struct GLFWwindow;

class WindowMain
{
public:
	static WindowMain& getInstance();

	~WindowMain();

	void initWindowMain();

	void executeEventLoop();

	const int& width() const { return width_; }
	const int& height() const { return height_; }
	const glm::vec2& curMousePos() const { return curMousePos_; }
	const glm::vec2& prevMousePos() const { return prevMousePos_; }
	const bool& pressMouseButtonRight() const { return pressMouseButtonRight_; }
	const bool& pressMouseButtonLeft() const { return pressMouseButtonLeft_; }
	const bool& pressKeyRight() const { return pressKeyRight_; }
	const bool& pressKeyLeft() const { return pressKeyLeft_; }
	const bool& pressKeyDown() const { return pressKeyDown_; }
	const bool& pressKeyUp() const { return pressKeyUp_; }
	const glm::vec3& backgroundColor() const { return backgroundColor_; }

private:
	WindowMain();

	GLFWwindow* glfwWindow_;
	int width_;
	int height_;
	glm::vec2 curMousePos_;
	glm::vec2 prevMousePos_;
	bool pressMouseButtonRight_;
	bool pressMouseButtonLeft_;
	bool pressKeyRight_;
	bool pressKeyLeft_;
	bool pressKeyDown_;
	bool pressKeyUp_;
	glm::vec3 backgroundColor_;
};