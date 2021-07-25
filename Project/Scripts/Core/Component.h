#pragma once
#include <string>
#include <iostream>
#include "BaseObject.h"
#include "IdHolder.h"

class BaseObject;

/// <summary>
/// Components will be watched by shared_ptr from it's holder BaseObject, and will be only exposed as weak_ptr.
/// </summary>
class Component : public IdHolder
{
	friend BaseObject;
private:
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;
	Component() = delete;

	bool enabled;

	virtual void OnEnableChanged(bool) { }

	/// <summary>
	/// Will be called when the component is added.
	/// </summary>
	virtual void Start() { }

	/// <summary>
	/// Will be called every frame.
	/// </summary>
	virtual void Update(float dt) { }
protected:
	std::weak_ptr<BaseObject> holder;
	bool transformChanged;

	Component(std::weak_ptr<BaseObject> holder)
	{
		enabled = true;
		this->holder = holder;
	}
public:
	virtual ~Component()
	{
	}

	bool GetEnabled()
	{
		return enabled;
	}

	void SetEnabled(bool enabled)
	{
		this->enabled = enabled;
		OnEnableChanged(enabled);
	}

	std::weak_ptr<BaseObject> GetHolder()
	{
		return holder;
	}
};

template <class T>
class TypedComponent : public Component
{
	friend BaseObject;
private:
	std::weak_ptr<T> selfRef;
protected:
	TypedComponent(std::weak_ptr<BaseObject> holder) : Component(holder)
	{
	}
public:
	std::weak_ptr<T> GetSelfReference()
	{
		return selfRef;
	}
};

template <class T>
std::string GetTypeName()
{
	std::cout << "It is not a component, or no GetTypeName has defined." << std::endl;
	return "";
}
