#pragma once
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <memory>

class Scene;

class Actor
{
public:
	Actor(std::weak_ptr<Scene> scene);
	virtual ~Actor();
	virtual void update() = 0;
	virtual void draw() = 0;

protected:
	std::weak_ptr<Scene> scene_;
};