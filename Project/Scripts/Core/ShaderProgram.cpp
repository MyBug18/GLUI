#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"
#include "Shader.h"
#include "Logger.h"

std::unordered_map<unsigned long, std::unique_ptr<ShaderProgram>> loadedPrograms;

ShaderProgram::ShaderProgram(GLuint ref, unsigned long hash)
{
	programRef = ref;
	programHash = hash;
}

const GLuint ShaderProgram::GetUniformLoc(std::string uniformName)
{
	auto foundIdx = uniformMap.find(uniformName);

	if (foundIdx != uniformMap.end())
	{
		return foundIdx->second;
	}

	return glGetUniformLocation(programRef, uniformName.c_str());
}

const unsigned long& ShaderProgram::GetProgramHash() const
{
	return programHash;
}

const GLuint& ShaderProgram::GetProgramRef() const
{
	return programRef;
}

void ShaderProgram::SetMatrix4x4(std::string uniformName, glm::mat4 mat, bool transpose)
{
	auto loc = GetUniformLoc(uniformName);
	glUniformMatrix4fv(loc, 1, transpose, glm::value_ptr(mat));
}

void ShaderProgram::SetVec4(std::string uniformName, glm::vec4 v)
{
	auto loc = GetUniformLoc(uniformName);
	glUniform4fv(loc, 1, glm::value_ptr(v));
}

void ShaderProgram::SetFloats(std::string uniformName, const float* floats, int count)
{
	auto loc = GetUniformLoc(uniformName);
	glUniform1fv(loc, count, floats);
}

void ShaderProgram::Use()
{
	if (programRef == 0) return;

	glUseProgram(programRef);
}

ShaderProgram* ShaderProgram::GetShaderProgram(std::vector<Shader*> shaders)
{
	unsigned long programHash = 0;
	for (auto& i : shaders)
	{
		programHash += i->GetId();
	}

	auto foundIdx = loadedPrograms.find(programHash);

	if (foundIdx != loadedPrograms.end())
	{
		return foundIdx->second.get();
	}

	auto programRef = glCreateProgram();

	for (auto& i : shaders)
	{
		glAttachShader(programRef, i->GetShaderRef());
	}

	glLinkProgram(programRef);
	Logger::CheckOpenGLError();

	GLint linked;
	glGetProgramiv(programRef, GL_LINK_STATUS, &linked);
	if (linked != 1)
	{
		Logger::PrintLog("Linking Failed");
		Logger::PrintProgramLog(programRef);
		return nullptr;
	}

	auto ptr = std::make_unique<ShaderProgram>(programRef, programHash);
	auto result = ptr.get();

	loadedPrograms[programHash] = std::move(ptr);
	return result;
}
