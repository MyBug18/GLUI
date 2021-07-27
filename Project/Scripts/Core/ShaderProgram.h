#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <string>

class Shader;

class ShaderProgram
{
private:
	GLuint programRef;
	unsigned long programHash;
	std::unordered_map<std::string, GLuint> uniformMap;
	const GLuint GetUniformLoc(std::string);
public:
	ShaderProgram(GLuint, unsigned long);

	const unsigned long& GetProgramHash() const;
	const GLuint& GetProgramRef() const;

	void SetMatrix4x4(std::string, glm::mat4, bool);
	void SetVec4(std::string, glm::vec4);
	void SetFloats(std::string, const float*, int);

	void Use();

	static ShaderProgram* GetShaderProgram(std::vector<Shader*>);
};
