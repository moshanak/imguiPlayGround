#include "GLSLPassthrough.h"

void GLSLPassthrough::build()
{
	std::string vs = R"(
#version 460
layout (location = 0) in vec3 VertexPosition;
uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(VertexPosition, 1.0f);
}
	)";

	std::string fs = R"(
#version 460
layout (location = 0) out vec4 FragColor;
uniform vec4 OutputColor;

void main()
{
	FragColor = OutputColor;
}
	)";

	compile(GL_VERTEX_SHADER, vs.c_str());
	compile(GL_FRAGMENT_SHADER, fs.c_str());

	link();
}