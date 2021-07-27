#pragma once

#include "Loadable.h"

typedef unsigned int GLuint;

class Shader : public Loadable
{
protected:
	GLuint shaderRef = 0;
	GLuint shaderType = 0;

	Shader(std::string filePath) : Loadable(filePath) { }
public:
	bool Load() override;
	void Unload() override;

	const GLuint& GetShaderType() const;
	const GLuint& GetShaderRef() const;

	static std::string ShaderTypeToString(GLuint type);
	static Shader* LoadShader(GLuint type, std::string filePath);
};
