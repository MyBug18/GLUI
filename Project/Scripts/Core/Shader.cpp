#include <GL/glew.h>
#include "Shader.h"
#include "Logger.h"
#include "ResourceHolder.h"

bool Shader::Load()
{
	shaderRef = glCreateShader(shaderType);

	if (shaderRef == 0 || shaderRef == GL_INVALID_ENUM)
	{
		printf("Error: Could not create shader \"%s\" of type:%d\n", filePath.c_str(), shaderType);
		return false;
	}

	const auto& shaderStr = Loadable::ReadResourceFileAsString(filePath);
	auto shaderSrc = shaderStr.c_str();

	glShaderSource(shaderRef, 1, &shaderSrc, NULL);
	glCompileShader(shaderRef);
	Logger::CheckOpenGLError();

	GLint shaderCompiled;
	glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &shaderCompiled);

	if (shaderCompiled != GL_TRUE)
	{
		Logger::PrintLog(ShaderTypeToString(shaderType) + " shader compilation error for shader: '" + filePath);
		Logger::PrintShaderLog(shaderRef);

		return false;
	}

	return true;
}

void Shader::Unload()
{
	glDeleteShader(shaderRef);
}

const GLuint& Shader::GetShaderRef() const
{
	return shaderRef;
}

const GLuint& Shader::GetShaderType() const
{
	return shaderType;
}

std::string Shader::ShaderTypeToString(GLuint type)
{
	switch (type)
	{
	case GL_VERTEX_SHADER:
		return "Vertex";
	case GL_FRAGMENT_SHADER:
		return "Fragment";
	case GL_TESS_CONTROL_SHADER:
		return "Tess Control";
	case GL_TESS_EVALUATION_SHADER:
		return "Tess Evaluation";
	case GL_GEOMETRY_SHADER:
		return "Geometry";
	case GL_COMPUTE_SHADER:
		return "Compute";
	}

	return "";
}

class VertexShader : public Shader
{
public:
	VertexShader(std::string filePath) : Shader(filePath)
	{
		shaderType = GL_VERTEX_SHADER;
	}
};

class FragmentShader : public Shader
{
public:
	FragmentShader(std::string filePath) : Shader(filePath)
	{
		shaderType = GL_FRAGMENT_SHADER;
	}
};

Shader* Shader::LoadShader(GLuint type, std::string filePath)
{
	switch (type)
	{
	case GL_VERTEX_SHADER:
		return ResourceHolder::Get<VertexShader>(filePath);
	case GL_FRAGMENT_SHADER:
		return ResourceHolder::Get<FragmentShader>(filePath);
	}

	Logger::PrintLog("Not defined shader type: " + type);
	return nullptr;
}
