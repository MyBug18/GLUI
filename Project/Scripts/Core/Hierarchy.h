#pragma once

#include <functional>
#include "GLShaderHolder.h"
#include "BaseObject.h"

class BaseObject;
class Mesh;

class Hierarchy
{
private:
	Hierarchy(const Hierarchy&) = delete;
	Hierarchy& operator=(const Hierarchy&) = delete;

	std::shared_ptr<BaseObject> topObject;

	std::vector<std::function<void()>> afterLoopCallbacks;

	std::unordered_map<int, std::vector<std::weak_ptr<Mesh>>> renderObjects;
public:
	Hierarchy();
	~Hierarchy();

	void Initialize();
	void Update(float dt);
	void Render();

	std::shared_ptr<BaseObject> GetTopObject();

	/// <summary>
	/// Register callbacks which will be executed after the hierarchy loop, right before the rendering.
	/// </summary>
	void RegisterAfterLoopCallback(std::function<void()>);

	void AddRenderObject(std::weak_ptr<Mesh>);
};
