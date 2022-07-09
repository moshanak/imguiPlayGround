#pragma once
#include "Actor.h"
#include <memory>
#include <vector>

class Scene
{
public:
	Scene();
	void draw();

private:
	std::vector<std::shared_ptr<Actor>> actors_;
};