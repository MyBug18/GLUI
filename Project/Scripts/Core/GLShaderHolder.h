#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <map>
#include <unordered_map>

class Shader
{
private:
	int shaderType;
	std::string shaderPath;
	GLuint shaderRef;
public:
	Shader();
	Shader(int, std::string, GLuint);
	~Shader();

	const int& GetShaderType() const;
	const std::string& GetShaderPath() const;
	const GLuint& GetShaderRef() const;
};

class ShaderProgram
{
private:
	GLuint programId;
	std::unordered_map<std::string, GLuint> uniformMap;
	const GLuint GetUniformLoc(std::string);
public:
	ShaderProgram();
	ShaderProgram(int);
	~ShaderProgram();

	const GLuint GetProgramId();
	void SetMatrix4x4(std::string, glm::mat4, bool);
	void SetVec4(std::string, glm::vec4);
	void SetFloats(std::string, const float*, int);
};

class GLShaderHolder
{
private:
	GLShaderHolder(const GLShaderHolder&) = delete;
	GLShaderHolder& operator=(const GLShaderHolder&) = delete;
	GLShaderHolder() = delete;
	~GLShaderHolder() = delete;
public:
	static Shader* LoadShader(int shaderType, std::string shaderPath);
	static ShaderProgram* LoadProgram(const std::map<int, Shader*>&);
	static ShaderProgram* GetProgramById(GLuint);
};
