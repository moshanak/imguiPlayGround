#pragma once
#include "GLSL.h"
#include <memory>
#include <unordered_map>

enum class GLSLType
{
	passthrough
};

class GLSLManager
{
public:
	static GLSLManager& getInstance();
	void buildAllGLSL();
	const GLSL& getGLSL(GLSLType type);

private:
	GLSLManager();
	std::unordered_map<GLSLType, std::unique_ptr<GLSL>> glslHashTable_;
};
