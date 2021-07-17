#include "SquareMesh.h"

int triangles[] = { 0, 1, 2, 1, 3, 2 };

SquareMesh::SquareMesh(std::weak_ptr<BaseObject> holder) : TypedComponent<SquareMesh>(holder), Mesh()
{
	verticesVbo = 0;
	SetSquareData(-1, -1, 1, 1);
}

void SquareMesh::Start()
{
	SetShaderData(GL_VERTEX_SHADER, "SquareMeshVert.glsl");
	SetShaderData(GL_FRAGMENT_SHADER, "RandomMeshFrag.glsl");
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
	{
		glGenBuffers(1, &verticesVbo);
		glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);
	}

	float vertices[12] = { downLeftX, downLeftY, downLeftX, upRightY, upRightX, downLeftY, downLeftX, upRightY, upRightX, upRightY, upRightX, downLeftY };
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW);
}

void SquareMesh::RenderThis(Camera* cam, ShaderProgram* program)
{
	if (holder.expired()) return;

	program->SetMatrix4x4("proj_matrix", cam->GetProjectionMatrix(), false);
	program->SetMatrix4x4("mv_matrix", cam->GetViewMatrix() * holder.lock()->GetWorldTransform(), false);

	glDrawArrays(GL_TRIANGLES, 0, 20);
}
