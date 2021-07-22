#pragma once

#include <glm/glm.hpp>
#include "../Core/Component.h"
#include "../Core/Mesh.h"

class SquareMesh : public TypedComponent<SquareMesh>, public Mesh
{
private:
	GLuint verticesVbo, trianglesVbo;

	glm::vec2 downLeft, upRight;

	void Start() override;
	void Update(float) override;
	void RenderThis(Camera*, ShaderProgram*) override;
public:
	SquareMesh(std::weak_ptr<BaseObject>);

	void SetSquareData(float downLeftX, float downLeftY, float upRightX, float upRightY);
};

template <>
inline std::string GetTypeName<SquareMesh>()
{
	return "SquareMesh";
}
