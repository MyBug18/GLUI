#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <map>
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

	std::map<int, Shader*> shaders;
	int layer;
public:
	void SetShaderData(int, std::string);
	void SetLayer(int);

	const std::map<int, Shader*>& GetShaderInfo();

	GLuint GetVaoId();

	virtual void RenderThis(Camera*, ShaderProgram*) { }
};
