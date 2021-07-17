#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <glm/gtc/quaternion.hpp>
#include "Component.h"
#include "App.h"

class Component;
class Hierarchy;
class App;

template <typename T>
class TypedComponent;

class BaseObject
{
	// For the top object to set it's selfRef, directly controlled by Hierarchy.
	friend Hierarchy;
private:
	BaseObject(const BaseObject&) = delete;
	BaseObject& operator=(const BaseObject&) = delete;

	int guid;

	// The weak pointer from it's parent's pointer pointing this object.
	std::weak_ptr<BaseObject> selfRef;

	std::weak_ptr<BaseObject> parent;
	std::vector<std::shared_ptr<BaseObject>> children;
	std::unordered_map<std::string, std::shared_ptr<Component>> components;

	bool isTransformChanged;
	glm::mat4 localTransform;
	glm::mat4 worldTransform;

	void SetTransformChanged();
	void RecalculateTransform();

	glm::vec3 localPosition;
	glm::quat localRotation;
	glm::vec3 localScale;

public:

	BaseObject(std::weak_ptr<BaseObject>);
	BaseObject(std::weak_ptr<BaseObject>, int);

	~BaseObject();

	/// <summary>
	/// Compares it's guid only.
	/// </summary>
	bool operator==(BaseObject&);

	int GetGuid();

	std::weak_ptr<BaseObject> GetSelfReference();

	/// <summary>
	/// Instantiates a new BaseObject and attach it as it's child.
	/// The added object can immediately access it's parent, but being added as a child of parent will be the next frame.
	/// </summary>
	std::weak_ptr<BaseObject> Instantiate();

	/// <summary>
	/// Detaches from it's parent and attach to this object as a child.
	/// </summary>
	void AddChild(std::shared_ptr<BaseObject>);

	/// <summary>
	/// Returns the child of this BaseObject with the index.
	/// </summary>
	std::weak_ptr<BaseObject> GetChild(size_t index);
	size_t GetChildCount();

	/// <summary>
	/// Adds the component to this object. The component will be added on the next frame and then the Start() will be called.
	/// </summary>
	template <class T>
	std::weak_ptr<T> AddComponent()
	{
		auto name = GetTypeName<T>();

		if (name == "") return std::weak_ptr<T>();

		auto c = components.find(name);
		if (c != components.end())
		{
			return std::dynamic_pointer_cast<T>(c->second);
		}

		auto ptr = std::make_shared<T>(GetSelfReference());
		ptr->selfRef = ptr;

		App::Instance()->GetHierarchy()->RegisterAfterLoopCallback([&, name, ptr]()
			{
				auto cPtr = std::dynamic_pointer_cast<Component>(ptr);

				components[name] = cPtr;
				cPtr->Start();
			});

		return ptr;
	}

	template <class T>
	std::weak_ptr<T> GetComponent()
	{
		auto c = components.find(GetTypeName<T>());
		if (c == components.end())
		{
			return std::weak_ptr<T>();
		}

		return std::dynamic_pointer_cast<T>(c->second);
	}

	void Update(float);

	const glm::vec3 GetWorldPosition();
	const glm::mat4& GetWorldTransform();

	const glm::vec3& GetLocalPosition();

	void SetLocalPosition(glm::vec3);
	void SetLocalPosition(float x, float y, float z);

	void Translate(glm::vec3);
	void Translate(float x, float y, float z);

	void RotateAxis(glm::vec3 axis, float rad);
	void RotateAxis(float x, float y, float z, float rad);

	void SetScale(glm::vec3 scale);
	void SetScale(float x, float y, float z);

	void LookAt(glm::vec3 to);
	void LookAt(float x, float y, float z);
};
