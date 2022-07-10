#include "GLSLManager.h"
#include "GLSLPassthrough.h"

GLSLManager& GLSLManager::getInstance()
{
	static GLSLManager instance_;
	return instance_;
}

void GLSLManager::buildAllGLSL()
{
	for (auto& glsl : glslHashTable_)
	{
		glsl.second->build();
	}
}

GLuint GLSLManager::getProgramHandle(GLSLType type)
{
	return glslHashTable_[type]->getProgram();
}

GLSLManager::GLSLManager()
{
	glslHashTable_.emplace(GLSLType::passthrough, std::make_unique<GLSLPassthrough>());
}