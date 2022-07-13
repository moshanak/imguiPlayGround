#pragma once
#include "GLSL.h"
#include <glm/glm.hpp>

class GLSLPassthrough : public GLSL
{
public:
	void build() final;
	void setMVP(const glm::mat4& mvp) const;
	void setOutputColor(const glm::vec4& outputColor) const;
};
