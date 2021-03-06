#include <GL/glew.h>
#include "Hierarchy.h"
#include "Mesh.h"
#include "BaseObject.h"
#include "Camera.h"
#include "ShaderProgram.h"

Hierarchy::Hierarchy()
{
}

Hierarchy::~Hierarchy()
{
}

void Hierarchy::Initialize()
{
	// Top object have no parent, so make a dummy weak pointer to act as a nullptr.
	topObject = std::make_shared<BaseObject>(std::weak_ptr<BaseObject>());
	topObject->selfRef = topObject;
}

void Hierarchy::Update(float dt)
{
	topObject->Update(dt);
}

void Hierarchy::AfterLoop()
{
	for (auto& f : afterLoopCallbacks)
	{
		f();
	}

	afterLoopCallbacks.clear();
}

std::shared_ptr<BaseObject> Hierarchy::GetTopObject()
{
	return topObject;
}

void Hierarchy::RegisterAfterLoopCallback(std::function<void()> f)
{
	afterLoopCallbacks.push_back(f);
}

void Hierarchy::AddRenderObject(std::weak_ptr<Mesh> meshRef)
{
	auto ptr = meshRef.lock();

	auto program = ShaderProgram::GetShaderProgram(ptr->GetShaders());

	renderObjects[program].push_back(meshRef);
}

void Hierarchy::Render()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto& c : Camera::GetCameras())
	{
		for (auto& i : renderObjects)
		{
			auto& program = i.first;
			program->Use();

			for (auto& o : i.second)
			{
				if (o.expired())
					continue;

				auto mesh = o.lock();

				glBindVertexArray(mesh->GetVaoId());

				// Every vertex shader should include PV matrix, to set it uniformly here.
				program->SetMatrix4x4("pv_matrix", c->GetProjectionMatrix() * c->GetViewMatrix(), false);
				mesh->RenderThis(program);
			}
		}
	}

	renderObjects.clear();
}
