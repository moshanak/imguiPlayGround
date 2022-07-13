#pragma once
#include "Actor.h"

class ActorBackground : public Actor
{
public:
	ActorBackground(std::weak_ptr<Scene> scene);
	~ActorBackground();
	void update() final;
	void draw() final;
};