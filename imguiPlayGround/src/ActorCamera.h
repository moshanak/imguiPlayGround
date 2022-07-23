#pragma once
#include "Actor.h"

class Scene;

class ActorCamera : public Actor
{
public:
	ActorCamera(std::weak_ptr<Scene> scene);
	~ActorCamera();
	void update() final;
	void draw() final;

protected:
	glm::vec3 eye_;
	glm::mat4 viewMat4_;
	glm::mat4 projMat4_;
	float yaw_;
	float pitch_;
};