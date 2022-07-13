#include "ActorCoordinateAxis.h"
#include "GLSLManager.h"
#include "GLSLPassthrough.h"
#include "Scene.h"
#include "WindowMain.h"
#include <array>
#include <glm/gtx/quaternion.hpp>
#include <vector>

ActorCoordinateAxis::ActorCoordinateAxis(std::weak_ptr<Scene> scene)
	: Actor(scene)
	, yaw_(0.0f)
	, pitch_(0.0f)
{
	modelMat4_ = glm::mat4(1.0f);
	mvpMat4_ = glm::mat4(1.0f);

	// clang-format off
	std::vector<float> coordinates = {
		0.0f,	0.0f,	0.0f,
		50.0f,	0.0f,	0.0f,
		0.0f,	0.0f,	0.0f,
		0.0f,	50.0f,	0.0f,
		0.0f,	0.0f,	0.0f,
		0.0f,	0.0f,	50.0f};
	// clang-format on

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
	WindowMain& windowMain = WindowMain::getInstance();
	if (windowMain.pressMouseButtonRight())
	{
		const glm::vec2 delta = (windowMain.curMousePos() - windowMain.prevMousePos()) * 0.004f;
		const glm::vec3 cUp = {0.0f, 1.0f, 0.0f};
		float sign = glm::rotate(glm::quat(glm::vec3(-pitch_, -yaw_, 0.0f)), cUp).y < 0 ? -1.0f : 1.0f;
		yaw_ += sign * delta.x;
		pitch_ += delta.y;
	}

	modelMat4_ = glm::toMat4(glm::quat(glm::vec3(-pitch_, -yaw_, 0.0f)));
	modelMat4_ = glm::inverse(modelMat4_);
	std::shared_ptr<Scene> scene = scene_.lock();
	mvpMat4_ = scene->getProjMat4() * scene->getViewMat4() * modelMat4_;
}

void ActorCoordinateAxis::draw()
{
	glDisable(GL_DEPTH_TEST);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, coordinateBuffer_);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	const GLSLPassthrough& glslPassthrough = static_cast<const GLSLPassthrough&>(GLSLManager::getInstance().getGLSL(GLSLType::passthrough));
	glslPassthrough.setMVP(mvpMat4_);

	glUseProgram(glslPassthrough.getProgram());
	glLineWidth(5.0f);
	glPointSize(10.0f);
	glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);
	glslPassthrough.setOutputColor(color);
	glDrawArrays(GL_LINES, 0, 2);
	glDrawArrays(GL_POINTS, 1, 1);
	color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	glslPassthrough.setOutputColor(color);
	glDrawArrays(GL_LINES, 2, 2);
	glDrawArrays(GL_POINTS, 3, 1);
	color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	glslPassthrough.setOutputColor(color);
	glDrawArrays(GL_LINES, 4, 2);
	glDrawArrays(GL_POINTS, 5, 1);
	glUseProgram(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
}
