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
};