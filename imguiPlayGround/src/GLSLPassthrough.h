#pragma once
#include "GLSL.h"

class GLSLPassthrough : public GLSL
{
public:
	void build() final;
};
