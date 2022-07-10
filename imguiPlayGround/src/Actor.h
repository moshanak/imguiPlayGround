#pragma once
#include <GL/glew.h>

class Actor
{
public:
	Actor();
	virtual ~Actor();
	virtual void update() = 0;
	virtual void draw() = 0;
};