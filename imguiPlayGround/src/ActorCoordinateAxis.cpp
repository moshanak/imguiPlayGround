#include "ActorCoordinateAxis.h"
#include "GLSLManager.h"
#include <array>
#include <vector>

ActorCoordinateAxis::ActorCoordinateAxis()
{
	std::vector<float> coordinates = {
		0.0f,
		0.0f,
		0.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		1.0f};

	glGenBuffers(1, &coordinateBuffer_);
	glBindBuffer(GL_ARRAY_BUFFER, coordinateBuffer_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * coordinates.size(), coordinates.data(), GL_STATIC_DRAW);
}

ActorCoordinateAxis::~ActorCoordinateAxis()
{
	glDeleteBuffers(1, &coordinateBuffer_);
	coordinateBuffer_ = 0;
}

void ActorCoordinateAxis::update()
{
}

void ActorCoordinateAxis::draw()
{
	glDisable(GL_DEPTH_TEST);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, coordinateBuffer_);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	const GLuint programHandle = GLSLManager::getInstance().getProgramHandle(GLSLType::passthrough);
	const std::array<float, 4> color = {1.0f, 1.0f, 0.0f, 1.0f};
	const GLuint partColorLocation = glGetUniformLocation(programHandle, "OutputColor");
	glProgramUniform4fv(programHandle, partColorLocation, 1, color.data());

	glUseProgram(programHandle);
	glDrawArrays(GL_LINES, 0, 6);
	glUseProgram(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
}
