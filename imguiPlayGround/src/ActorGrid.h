#pragma once
#include "Actor.h"

class ActorGrid : public Actor
{
public:
	ActorGrid(std::weak_ptr<Scene> scene);
	~ActorGrid();
	void update() final;
	void draw() final;

private:
	GLuint coordinateBuffer_;
	glm::mat4 mvpMat4_;
	int numOfPoints_;
};