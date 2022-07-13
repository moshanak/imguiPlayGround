#pragma once
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

class Actor
{
public:
	Actor();
	virtual ~Actor();
	virtual void update() = 0;
	virtual void draw() = 0;
};