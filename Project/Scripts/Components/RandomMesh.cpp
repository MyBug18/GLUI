#include <libqhullcpp/Qhull.h>
#include <libqhullcpp/QhullVertex.h>
#include <libqhullcpp/QhullVertexSet.h>
#include <libqhullcpp/QhullFacetList.h>
#include <libqhullcpp/RboxPoints.h>
#include "RandomMesh.h"

RandomMesh::RandomMesh(std::weak_ptr<BaseObject> holder) : TypedComponent<RandomMesh>(holder), Mesh()
{
	verticesVbo = 0;
}

void RandomMesh::Start()
{
	SetShaderData(GL_VERTEX_SHADER, "RandomMeshVert.glsl");
	SetShaderData(GL_FRAGMENT_SHADER, "RandomMeshFrag.glsl");
}

void RandomMesh::Update(float dt)
{
	App::Instance()->GetHierarchy()->AddRenderObject(GetSelfReference());
}

void RandomMesh::SetVerticeData(const char* rboxCommand)
{
	vertices.clear();

	orgQhull::RboxPoints rbox;
	rbox.appendPoints(rboxCommand);
	orgQhull::Qhull qhull;
	qhull.runQhull(rbox, "Qt");

	auto lst = qhull.facetList().toStdVector();

	for (auto i = 0; i < lst.size(); i++)
	{
		auto vs = lst[i].vertices().toStdVector();

		auto point0 = vs[0].point().toStdVector();
		auto point0Vec = glm::vec3(point0[0], point0[1], point0[2]);

		auto point1 = vs[1].point().toStdVector();
		auto point1Vec = glm::vec3(point1[0], point1[1], point1[2]);

		auto point2 = vs[2].point().toStdVector();
		auto point2Vec = glm::vec3(point2[0], point2[1], point2[2]);

		auto vec1 = point2Vec - point1Vec;
		auto vec2 = point2Vec - point0Vec;

		auto cross = glm::cross(vec1, vec2);

		auto n = lst[i].getBaseT()->normal;
		auto normal = glm::vec3((float)n[0], (float)n[1], (float)n[2]);

		auto dot = glm::dot(cross, normal);

		if (dot < 0)
		{
			auto temp = vs[0];
			vs[0] = vs[1];
			vs[1] = temp;
		}

		for (auto j = 0; j < vs.size(); j++)
		{
			auto points = vs[j].point().toStdVector();

			for (auto k = 0; k < points.size(); k++)
			{
				vertices.push_back((float)points[k]);
			}
		}
	}

	glBindVertexArray(vaoId);

	if (verticesVbo == 0)
	{
		glGenBuffers(1, &verticesVbo);
		glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, verticesVbo);
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
}

void RandomMesh::RenderThis(Camera* cam, ShaderProgram* program)
{
	if (holder.expired()) return;

	program->SetMatrix4x4("proj_matrix", cam->GetProjectionMatrix(), false);
	program->SetMatrix4x4("mv_matrix", cam->GetViewMatrix() * holder.lock()->GetWorldTransform(), false);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
}
