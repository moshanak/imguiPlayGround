#include "GLSL.h"
//#include "Logger.h"

GLSL::GLSL()
{
	program_ = glCreateProgram();
	if (program_ == 0)
	{
		// Logger::info("Failed to glCreateProgram.");
	}
}

GLSL::~GLSL()
{
	glDeleteShader(shader_);
	if (program_ != 0)
	{
		glDeleteProgram(program_);
		program_ = 0;
	}
}

void GLSL::compile(const GLenum& shaderType, const std::string& sourceCode)
{
	shader_ = glCreateShader(shaderType);
	if (shader_ == 0)
	{
		// Logger::info("Failed to glCreateShader.");
	}

	const char* sourceCodePointer = sourceCode.c_str();
	glShaderSource(shader_, 1, &sourceCodePointer, NULL);
	glCompileShader(shader_);
	GLint compileStatus;
	glGetShaderiv(shader_, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
	{
		GLint longLength;
		glGetShaderiv(shader_, GL_INFO_LOG_LENGTH, &longLength);
		if (0 < longLength)
		{
			std::string log;
			log.resize(longLength);
			// GLsizei dummy;
			//  glGetShaderInfoLog(shader_, longLength, &dummy, log.data());
			//   Logger::info(log.c_str());
		}
	}
	glAttachShader(program_, shader_);
}

void GLSL::link()
{
	glLinkProgram(program_);
	GLint linkStatus;
	glGetProgramiv(program_, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE)
	{
		GLint logLength;
		glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &logLength);
		if (0 < logLength)
		{
			std::string log;
			log.resize(logLength);
			// GLsizei dummy;
			//  glGetProgramInfoLog(program_, logLength, &dummy, log.data());
			//   Logger::info(log.c_str());
		}
	}
}