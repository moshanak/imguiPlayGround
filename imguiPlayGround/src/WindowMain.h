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
	const double& getX() const { return x_; }
	const double& getY() const { return y_; }
	const double& getprevX() const { return prevx_; }
	const double& getprevY() const { return prevy_; }
	const bool& pushRight() const { return pushRight_; }

private:
	WindowMain();

	GLFWwindow* glfwWindow_;
	int width_;
	int height_;
	double x_;
	double y_;
	double prevx_;
	double prevy_;
	bool pushRight_;
};