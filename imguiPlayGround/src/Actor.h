#pragma once

class Actor
{
public:
	Actor();
	virtual ~Actor();
	virtual void draw() = 0;
};