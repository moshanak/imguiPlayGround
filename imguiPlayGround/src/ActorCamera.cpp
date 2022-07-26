#include "ActorCamera.h"
#include "Scene.h"
#include "WindowMain.h"
#include <glm/gtx/quaternion.hpp>

ActorCamera::ActorCamera(std::weak_ptr<Scene> scene)
	: Actor(scene)
	, yaw_(0.0f)
	, pitch_(0.0f)
{
	eye_ = glm::vec3(0, 0, 500);
}

ActorCamera::~ActorCamera()
{
}

void ActorCamera::update()
{
	WindowMain& windowMain = WindowMain::getInstance();
	if (windowMain.pressMouseButtonLeft())
	{
		const glm::vec2 delta = (windowMain.curMousePos() - windowMain.prevMousePos()) * 0.004f;
		const glm::vec3 cUp = {0.0f, 1.0f, 0.0f};
		float sign = glm::rotate(glm::quat(glm::vec3(-pitch_, -yaw_, 0.0f)), cUp).y < 0 ? -1.0f : 1.0f;
		yaw_ += sign * delta.x;
		pitch_ += delta.y;
	}
	glm::mat4x4 mat4 = glm::toMat4(glm::quat(glm::vec3(-pitch_, -yaw_, 0.0f)));
	mat4 = glm::inverse(mat4);

	glm::vec4 moveHorizontal(5, 0, 0, 1);
	moveHorizontal = mat4 * moveHorizontal;
	if (windowMain.pressKeyLeft())
	{
		eye_ -= glm::vec3(moveHorizontal);
	}
	if (windowMain.pressKeyRight())
	{
		eye_ += glm::vec3(moveHorizontal);
	}
	glm::vec4 moveVertical(0, 5, 0, 1);
	moveVertical = mat4 * moveVertical;
	if (windowMain.pressKeyDown())
	{
		eye_ -= glm::vec3(moveVertical);
	}
	if (windowMain.pressKeyUp())
	{
		eye_ += glm::vec3(moveVertical);
	}

	glm::vec3 center = glm::vec4(eye_, 1) + mat4 * glm::vec4(0, 0, -1, 1);
	glm::vec3 up = mat4 * glm::vec4(0, 1, 0, 1);
	viewMat4_ = glm::lookAt(eye_, center, up);
	scene_.lock()->setViewMat4(viewMat4_);

	// projMat4_ = glm::perspective(glm::radians(45.f), 1.33f, 0.1f, 1000.f);
	float halfWidth = 0.5f * static_cast<float>(windowMain.width());
	float halfHeight = 0.5f * static_cast<float>(windowMain.height());
	float base = std::max(halfWidth, halfHeight);
	halfWidth = halfWidth / base * 1000.0f;
	halfHeight = halfHeight / base * 1000.0f;
	projMat4_ = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, 0.1f, 100000.0f);
	scene_.lock()->setProjMat4(projMat4_);
}

void ActorCamera::draw()
{
}
