#pragma once
#include "Actor.h"

class ActorCoordinateAxis : public Actor
{
public:
	ActorCoordinateAxis();
	~ActorCoordinateAxis();
	void draw() final;
};