#include "Hierarchy.h"
#include "Camera.h"
#include "GLShaderHolder.h"
#include "Mesh.h"

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

	auto cameraHolder = topObject->Instantiate().lock();
	cameraHolder->AddComponent<Camera>();
	cameraHolder->SetLocalPosition(glm::vec3(0, 0, -5));
}

void Hierarchy::Update(float dt)
{
	topObject->Update(dt);

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

	auto program = GLShaderHolder::LoadProgram(ptr->GetShaderInfo());

	renderObjects[program->GetProgramId()].push_back(meshRef);
}

void Hierarchy::Render()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto& c : Camera::GetCameras())
	{
		if (c.expired()) continue;
		auto cam = c.lock();

		for (auto& i : renderObjects)
		{
			auto program = GLShaderHolder::GetProgramById(i.first);
			auto programId = program->GetProgramId();
			if (programId == 0) continue;

			glUseProgram(programId);

			for (auto& o : i.second)
			{
				if (o.expired())
					continue;

				auto mesh = o.lock();

				glBindVertexArray(mesh->GetVaoId());
				mesh->RenderThis(cam.get(), program);
			}
		}
	}

	renderObjects.clear();
}
