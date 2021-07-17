#pragma once

#include <GL/glew.h>
#include <iostream>

class Logger
{
private:
	Logger() = delete;
public:
	static void PrintShaderLog(GLuint);
	static void PrintProgramLog(GLuint);
	static bool CheckOpenGLError();
};
