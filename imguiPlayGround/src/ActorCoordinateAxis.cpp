#include "ActorCoordinateAxis.h"
#include "GLSLManager.h"
#include "WindowMain.h"
#include <array>
#include <glm/gtx/quaternion.hpp>
#include <vector>

ActorCoordinateAxis::ActorCoordinateAxis()
{
	viewMat4_ = glm::lookAt(glm::vec3(0, 0, 0.1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	modelMat4_ = glm::mat4(1.0f);
	mvpMat4_ = glm::mat4(1.0f);

	std::vector<float> coordinates = {
		0.0f,
		0.0f,
		0.0f,
		50.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		50.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		50.0f};

	glGenBuffers(1, &coordinateBuffer_);
	glBindBuffer(GL_ARRAY_BUFFER, coordinateBuffer_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * coordinates.size(), coordinates.data(), GL_STATIC_DRAW);
}

ActorCoordinateAxis::~ActorCoordinateAxis()
{
	glDeleteBuffers(1, &coordinateBuffer_);
	coordinateBuffer_ = 0;
}

float mYaw = 0.0f;
float mPitch = 0.0f;

glm::quat get_direction()
{
	return glm::quat(glm::vec3(-mPitch, -mYaw, 0.0f));
}

glm::vec3 get_up()
{
	const glm::vec3 cUp = {0.0f, 1.0f, 0.0f};
	return glm::rotate(get_direction(), cUp);
}

glm::vec3 get_right()
{
	const glm::vec3 cRight = {1.0f, 0.0f, 0.0f};
	return glm::rotate(get_direction(), cRight);
}

glm::vec3 get_forward()
{
	const glm::vec3 cForward = {0.0f, 0.0f, -1.0f};
	return glm::rotate(get_direction(), cForward);
}

void ActorCoordinateAxis::update()
{

	WindowMain& windowMain = WindowMain::getInstance();
	if (windowMain.pushRight())
	{
		glm::vec2 curPos(windowMain.getX(), windowMain.getY());
		glm::vec2 prevPos(windowMain.getprevX(), windowMain.getprevY());
		glm::vec2 delta = (curPos - prevPos) * 0.004f;
		float cRotationSpeed = 1.0f;

		float sign = get_up().y < 0 ? -1.0f : 1.0f;
		mYaw += sign * delta.x * cRotationSpeed;
		mPitch += delta.y * cRotationSpeed;
	}

	// projMat4_ = glm::perspective(glm::radians(45.f), 1.33f, 0.1f, 10.f);
	const float halfWidth = 0.5f * static_cast<float>(windowMain.getWidth());
	const float halfHeight = 0.5f * static_cast<float>(windowMain.getHeight());
	projMat4_ = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -60.0f, 60.0f);

	// modelMat4_ = glm::rotate(modelMat4_, 0.1f, glm::vec3(0, 0, 1));
	modelMat4_ = glm::toMat4(get_direction());
	modelMat4_ = glm::inverse(modelMat4_);
	/// glm::qua
	mvpMat4_ = projMat4_ * viewMat4_ * modelMat4_;
}

void ActorCoordinateAxis::draw()
{
	glDisable(GL_DEPTH_TEST);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, coordinateBuffer_);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	const GLuint programHandle = GLSLManager::getInstance().getProgramHandle(GLSLType::passthrough);

	const GLuint mvpLocation = glGetUniformLocation(programHandle, "MVP");
	glProgramUniformMatrix4fv(programHandle, mvpLocation, 1, false, &mvpMat4_[0][0]);
	const GLuint colorLocation = glGetUniformLocation(programHandle, "OutputColor");

	glUseProgram(programHandle);
	glLineWidth(5.0f);
	glPointSize(10.0f);
	glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);
	glProgramUniform4fv(programHandle, colorLocation, 1, &color[0]);
	glDrawArrays(GL_LINES, 0, 2);
	glDrawArrays(GL_POINTS, 1, 1);
	color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	glProgramUniform4fv(programHandle, colorLocation, 1, &color[0]);
	glDrawArrays(GL_LINES, 2, 2);
	glDrawArrays(GL_POINTS, 3, 1);
	color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	glProgramUniform4fv(programHandle, colorLocation, 1, &color[0]);
	glDrawArrays(GL_LINES, 4, 2);
	glDrawArrays(GL_POINTS, 5, 1);
	glUseProgram(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
}
