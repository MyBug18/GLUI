#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>

typedef unsigned int GLuint;

class BaseObject;
class Camera;
class Shader;
class ShaderProgram;

class Mesh
{
private:
	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

protected:
	Mesh();
	~Mesh();

	GLuint vaoId;

	std::unordered_map<int, Shader*> shaders;
	int layer;
public:
	void SetShaderData(int, std::string);
	void SetLayer(int);

	std::vector<Shader*> GetShaders();

	GLuint GetVaoId();

	virtual void RenderThis(Camera*, ShaderProgram*) { }
};
