#pragma once
#include "Actor.h"

class ActorCoordinateAxis : public Actor
{
public:
	ActorCoordinateAxis();
	~ActorCoordinateAxis();
	void update() final;
	void draw() final;

private:
	GLuint coordinateBuffer_;
	glm::mat4 projMat4_;
	glm::mat4 viewMat4_;
	glm::mat4 modelMat4_;
	glm::mat4 mvpMat4_;
};