#include "ActorGrid.h"
#include "GLSLManager.h"
#include "GLSLPassthrough.h"
#include "Scene.h"
#include "WindowMain.h"
#include <array>
#include <glm/gtx/quaternion.hpp>
#include <vector>

ActorGrid::ActorGrid(std::weak_ptr<Scene> scene)
	: Actor(scene)
{
	mvpMat4_ = glm::mat4();
	const int numOfLines = 1000;
	const float interval = 100.0f;
	const float limitCoordinates = static_cast<float>(numOfLines) * interval;
	std::vector<glm::vec3> coordinates;
	for (int i = 1; i <= numOfLines; ++i)
	{
		const float currentCoordinates = static_cast<float>(i) * interval;
		coordinates.emplace_back(currentCoordinates, -limitCoordinates, 0.0f);
		coordinates.emplace_back(currentCoordinates, limitCoordinates, 0.0f);

		coordinates.emplace_back(-currentCoordinates, -limitCoordinates, 0.0f);
		coordinates.emplace_back(-currentCoordinates, limitCoordinates, 0.0f);

		coordinates.emplace_back(-limitCoordinates, currentCoordinates, 0.0f);
		coordinates.emplace_back(limitCoordinates, currentCoordinates, 0.0f);

		coordinates.emplace_back(-limitCoordinates, -currentCoordinates, 0.0f);
		coordinates.emplace_back(limitCoordinates, -currentCoordinates, 0.0f);
	}

	// X axis
	coordinates.emplace_back(-limitCoordinates, 0.0f, 0.0f);
	coordinates.emplace_back(limitCoordinates, 0.0f, 0.0f);

	// Y axis
	coordinates.emplace_back(0.0f, -limitCoordinates, 0.0f);
	coordinates.emplace_back(0.0f, limitCoordinates, 0.0f);

	numOfPoints_ = static_cast<int>(coordinates.size());

	glGenBuffers(1, &coordinateBuffer_);
	glBindBuffer(GL_ARRAY_BUFFER, coordinateBuffer_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * coordinates.size(), coordinates.data(), GL_STATIC_DRAW);
}

ActorGrid::~ActorGrid()
{
	glDeleteBuffers(1, &coordinateBuffer_);
	coordinateBuffer_ = 0;
}

void ActorGrid::update()
{
	std::shared_ptr<Scene> scene = scene_.lock();
	mvpMat4_ = scene->getProjMat4() * scene->getViewMat4();
}

void ActorGrid::draw()
{
	glDisable(GL_DEPTH_TEST);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, coordinateBuffer_);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	const GLSLPassthrough& glslPassthrough = static_cast<const GLSLPassthrough&>(GLSLManager::getInstance().getGLSL(GLSLType::passthrough));
	glslPassthrough.setMVP(mvpMat4_);

	glUseProgram(glslPassthrough.getProgram());
	glLineWidth(1.0f);
	glm::vec4 color(0.5f, 0.5f, 0.5f, 1.0f);
	glslPassthrough.setOutputColor(color);
	glDrawArrays(GL_LINES, 0, numOfPoints_ - 4);
	color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	glslPassthrough.setOutputColor(color);
	glDrawArrays(GL_LINES, numOfPoints_ - 4, 2);
	color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	glslPassthrough.setOutputColor(color);
	glDrawArrays(GL_LINES, numOfPoints_ - 2, 2);
	glUseProgram(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
}
