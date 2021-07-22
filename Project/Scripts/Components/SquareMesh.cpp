#include "SquareMesh.h"

int triangles[] = { 0, 1, 2, 1, 3, 2 };

SquareMesh::SquareMesh(std::weak_ptr<BaseObject> holder) : TypedComponent<SquareMesh>(holder), Mesh()
{
	verticesVbo = 0;
	trianglesVbo = 0;

	downLeft = glm::vec2(0, 0);
	upRight = glm::vec2(0, 0);
}

void SquareMesh::Start()
{
	SetShaderData(GL_VERTEX_SHADER, "SquareMeshVert.glsl");
	SetShaderData(GL_FRAGMENT_SHADER, "RandomMeshFrag.glsl");

	glBindVertexArray(vaoId);

	glGenBuffers(1, &trianglesVbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, trianglesVbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6, triangles, GL_STATIC_DRAW);
}

void SquareMesh::Update(float dt)
{
	App::Instance()->GetHierarchy()->AddRenderObject(GetSelfReference());
}

void SquareMesh::SetSquareData(float downLeftX, float downLeftY, float upRightX, float upRightY)
{
	downLeft = glm::vec2(downLeftX, downLeftY);
	upRight = glm::vec2(upRightX, upRightY);

	glBindVertexArray(vaoId);

	if (verticesVbo == 0)
		glGenBuffers(1, &verticesVbo);
	glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);

	float vertices[8] = { downLeftX, downLeftY, downLeftX, upRightY, upRightX, downLeftY, upRightX, upRightY };
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}

void SquareMesh::RenderThis(Camera* cam, ShaderProgram* program)
{
	if (holder.expired()) return;

	program->SetMatrix4x4("model_matrix", holder.lock()->GetWorldTransform(), false);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}
