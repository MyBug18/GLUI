#include <GL/glew.h>
#include <iostream>
#include "Logger.h"

void Logger::PrintLog(std::string s)
{
	std::cout << s << std::endl;
}

void Logger::PrintShaderLog(GLuint shader)
{
	auto len = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

	if (len <= 0) return;

	std::string log(0, ' ');
	auto chWrittn = 0;
	glGetShaderInfoLog(shader, len, &chWrittn, &log[0]);
	std::cout << "Shader Info Log: " << log << std::endl;
}

void Logger::PrintProgramLog(GLuint prog)
{
	auto len = 0;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);

	if (len <= 0) return;

	std::string log(0, ' ');
	auto chWrittn = 0;
	glGetProgramInfoLog(prog, len, &chWrittn, &log[0]);
	std::cout << "Program Info Log: " << log << std::endl;
}

bool Logger::CheckOpenGLError()
{
	auto foundError = false;
	auto glErr = glGetError();
	while (glErr != GL_NO_ERROR)
	{
		std::cout << "glError: " << glErr << std::endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}
