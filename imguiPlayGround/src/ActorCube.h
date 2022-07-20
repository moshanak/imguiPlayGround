#pragma once
#include "Actor.h"

class ActorCube : public Actor
{
public:
	ActorCube(std::weak_ptr<Scene> scene);
	~ActorCube();
	void update() final;
	void draw() final;

private:
	GLuint coordinateBuffer_;
	glm::mat4 modelMat4_;
	glm::mat4 mvpMat4_;
	float yaw_;
	float pitch_;
};