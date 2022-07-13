#pragma once
#include "Actor.h"

class ActorCoordinateAxis : public Actor
{
public:
	ActorCoordinateAxis(std::weak_ptr<Scene> scene);
	~ActorCoordinateAxis();
	void update() final;
	void draw() final;

private:
	GLuint coordinateBuffer_;
	glm::mat4 modelMat4_;
	glm::mat4 mvpMat4_;
	float yaw_;
	float pitch_;
};