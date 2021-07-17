#pragma once

#include "../Core/Component.h"
#include "../Core/Mesh.h"

class RandomMesh : public TypedComponent<RandomMesh>, public Mesh
{
private:
	GLuint verticesVbo;
	std::vector<float> vertices;

	void Start() override;
	void Update(float) override;
	void RenderThis(Camera*, ShaderProgram*) override;
public:
	RandomMesh(std::weak_ptr<BaseObject>);
	void SetVerticeData(const char* rboxCommand);
};

template <>
inline std::string GetTypeName<RandomMesh>()
{
	return "RandomMesh";
}
