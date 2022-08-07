#include "GLSL.h"
#include <iostream>

GLSL::GLSL()
	: program_(0)
	, shader_(0)
{
	program_ = glCreateProgram();
}

GLSL::~GLSL()
{
	glDeleteShader(shader_);
	glDeleteProgram(program_);
}

void GLSL::compile(const GLenum& shaderType, const std::string& sourceCode)
{
	shader_ = glCreateShader(shaderType);
	const char* sourceCodePointer = sourceCode.c_str();
	glShaderSource(shader_, 1, &sourceCodePointer, NULL);
	glCompileShader(shader_);
	GLint compileStatus;
	glGetShaderiv(shader_, GL_COMPILE_STATUS, &compileStatus);
	glAttachShader(program_, shader_);
}

void GLSL::link()
{
	glLinkProgram(program_);
	GLint linkStatus;
	glGetProgramiv(program_, GL_LINK_STATUS, &linkStatus);
}