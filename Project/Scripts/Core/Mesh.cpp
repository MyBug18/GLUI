#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.h"
#include "App.h"
#include "GLShaderHolder.h"

Mesh::Mesh()
{
	glGenVertexArrays(1, &vaoId);
	layer = 0;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vaoId);
}

void Mesh::SetShaderData(int shaderType, std::string shaderPath)
{
	shaders[shaderType] = GLShaderHolder::LoadShader(shaderType, shaderPath);
}

void Mesh::SetLayer(int l)
{
	layer = l;
}

const std::map<int, Shader*>& Mesh::GetShaderInfo()
{
	return shaders;
}

GLuint Mesh::GetVaoId()
{
	return vaoId;
}
