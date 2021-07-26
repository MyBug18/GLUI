#pragma once

#include <iostream>

typedef unsigned int GLuint;

class Logger
{
private:
	Logger() = delete;
public:
	static void PrintLog(std::string);
	static void PrintShaderLog(GLuint);
	static void PrintProgramLog(GLuint);
	static bool CheckOpenGLError();
};
