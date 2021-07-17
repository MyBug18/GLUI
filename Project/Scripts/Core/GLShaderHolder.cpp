#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <glm/gtc/type_ptr.hpp>
#include "GLShaderHolder.h"
#include "Logger.h"

std::unordered_map<std::string, std::unique_ptr<Shader>> createdShaderMap;
std::unordered_map<size_t, std::unique_ptr<ShaderProgram>> createdProgramMap;

auto invalidShader = std::make_unique<Shader>();
auto invalidProgram = std::make_unique<ShaderProgram>();

size_t GetShaderInfoHash(const std::map<int, Shader*>& shaderInfo)
{
	auto seed = shaderInfo.size();

	for (auto& i : shaderInfo)
	{
		seed ^= (size_t)i.second->GetShaderRef() + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	return seed;
}

Shader::Shader()
{
	shaderType = 0;
	shaderPath = "";
	shaderRef = 0;
}

Shader::Shader(int shaderType, std::string shaderPath, GLuint shaderRef)
{
	this->shaderType = shaderType;
	this->shaderPath = shaderPath;
	this->shaderRef = shaderRef;
}

Shader::~Shader()
{
	glDeleteShader(shaderRef);
}

const int& Shader::GetShaderType() const
{
	return shaderType;
}

const std::string& Shader::GetShaderPath() const
{
	return shaderPath;
}

const GLuint& Shader::GetShaderRef() const
{
	return shaderRef;
}

ShaderProgram::ShaderProgram()
{
	programId = 0;
}

ShaderProgram::ShaderProgram(int programId)
{
	this->programId = programId;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(programId);
}

const GLuint ShaderProgram::GetProgramId()
{
	return programId;
}

const GLuint ShaderProgram::GetUniformLoc(std::string uniformName)
{
	auto foundIdx = uniformMap.find(uniformName);

	if (foundIdx != uniformMap.end())
	{
		return foundIdx->second;
	}

	return glGetUniformLocation(programId, uniformName.c_str());
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

const std::string ReadShaderFile(std::string filePath)
{
	std::ifstream fileStream("Resources/" + filePath, std::ios::in);
	if (!fileStream.is_open())
	{
		throw "Unable to open file.";
	}

	std::string content;
	std::string line = "";

	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	return content;
}

Shader* GLShaderHolder::LoadShader(int shaderType, std::string path)
{
	GLuint shaderRef;
	auto foundIdx = createdShaderMap.find(path);

	if (foundIdx != createdShaderMap.end())
	{
		return foundIdx->second.get();
	}

	GLint shaderCompiled;
	shaderRef = glCreateShader(shaderType);

	const auto& shaderStr = ReadShaderFile(path);
	auto shaderSrc = shaderStr.c_str();

	if (shaderRef == 0 || shaderRef == GL_INVALID_ENUM)
	{
		printf("Error: Could not create shader \"%s\" of type:%d\n", path.c_str(), shaderType);
		return invalidShader.get();
	}

	glShaderSource(shaderRef, 1, &shaderSrc, NULL);
	glCompileShader(shaderRef);
	Logger::CheckOpenGLError();

	glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &shaderCompiled);

	if (shaderCompiled != GL_TRUE)
	{
		if (shaderType == GL_VERTEX_SHADER) std::cout << "Vertex ";
		if (shaderType == GL_TESS_CONTROL_SHADER) std::cout << "Tess Control ";
		if (shaderType == GL_TESS_EVALUATION_SHADER) std::cout << "Tess Eval ";
		if (shaderType == GL_GEOMETRY_SHADER) std::cout << "Geometry ";
		if (shaderType == GL_FRAGMENT_SHADER) std::cout << "Fragment ";
		if (shaderType == GL_COMPUTE_SHADER) std::cout << "Compute ";
		std::cout << "shader compilation error for shader: '" << path << "'." << std::endl;
		Logger::PrintShaderLog(shaderRef);
	}

	auto ptr = std::make_unique<Shader>(shaderType, path, shaderRef);
	auto result = ptr.get();
	createdShaderMap[path] = std::move(ptr);
	return result;
}

ShaderProgram* GLShaderHolder::LoadProgram(const std::map<int, Shader*>& shaderInfo)
{
	auto shaderInfoHash = GetShaderInfoHash(shaderInfo);

	auto foundIdx = createdProgramMap.find(shaderInfoHash);

	if (foundIdx != createdProgramMap.end())
	{
		return foundIdx->second.get();
	}

	auto programId = glCreateProgram();

	for (auto& i : shaderInfo)
	{
		glAttachShader(programId, i.second->GetShaderRef());
	}

	glLinkProgram(programId);
	Logger::CheckOpenGLError();

	GLint linked;
	glGetProgramiv(programId, GL_LINK_STATUS, &linked);
	if (linked != 1)
	{
		std::cout << "linking failed" << std::endl;
		Logger::PrintProgramLog(programId);
		programId = 0;
	}

	auto ptr = std::make_unique<ShaderProgram>(programId);
	auto result = ptr.get();

	createdProgramMap[shaderInfoHash] = std::move(ptr);
	return result;
}

ShaderProgram* GLShaderHolder::GetProgramById(GLuint Id)
{
	for (auto& i : createdProgramMap)
	{
		if (i.second->GetProgramId() == Id)
			return i.second.get();
	}

	return invalidProgram.get();
}
