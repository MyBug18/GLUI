#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.h"
#include "App.h"
#include "Shader.h"

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
	shaders[shaderType] = Shader::LoadShader(shaderType, shaderPath);
}

void Mesh::SetLayer(int l)
{
	layer = l;
}

std::vector<Shader*> Mesh::GetShaders()
{
	std::vector<Shader*> result;

	for (auto& i : shaders)
		result.push_back(i.second);

	return result;
}

GLuint Mesh::GetVaoId()
{
	return vaoId;
}
