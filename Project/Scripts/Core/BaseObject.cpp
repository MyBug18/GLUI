#include <cstdlib>
#include <glm/gtc/matrix_transform.hpp>
#include "BaseObject.h"
#include "App.h"
#include "Rotation.h"

BaseObject::BaseObject(std::weak_ptr<BaseObject> parent) : BaseObject(parent, rand())
{
}

BaseObject::BaseObject(std::weak_ptr<BaseObject> parent, int guid)
{
	this->parent = parent;
	this->guid = guid;

	isTransformChanged = true;

	localPosition = glm::vec3(0);
	localRotation = glm::identity<glm::quat>();
	localScale = glm::vec3(1);

	localTransform = glm::mat4(1);
	worldTransform = glm::mat4(1);
}

BaseObject::~BaseObject()
{
}

bool BaseObject::operator==(BaseObject& other)
{
	return guid == other.guid;
}

int BaseObject::GetGuid()
{
	return guid;
}

std::weak_ptr<BaseObject> BaseObject::GetSelfReference()
{
	return selfRef;
}

std::weak_ptr<BaseObject> BaseObject::Instantiate()
{
	auto newObject = std::make_shared<BaseObject>(selfRef);
	newObject->selfRef = newObject;

	auto h = App::Instance()->GetHierarchy();

	h->RegisterAfterLoopCallback([&, newObject]()
		{
			if (selfRef.expired()) return;

			children.push_back(newObject);
		});

	return newObject;
}

void BaseObject::AddChild(std::shared_ptr<BaseObject> childObj)
{
	// Can't add the top object as another object's child.
	if (childObj->parent.expired()) return;

	App::Instance()->GetHierarchy()->RegisterAfterLoopCallback([this, childObj]()
		{
			auto parent = childObj->parent.lock();
			auto& siblings = parent->children;

			// First find the child itself from the parent's children.
			size_t i;
			for (i = 0; i < siblings.size(); i++)
			{
				if (childObj->guid != siblings[i]->guid) continue;
				break;
			}

			// Cut it's connection to parent and reassign it to this.
			parent->children.erase(parent->children.begin() + i);
			childObj->parent = selfRef;
		});
}

std::weak_ptr<BaseObject> BaseObject::GetChild(size_t index)
{
	if (index < 0 || index >= children.size()) return std::weak_ptr<BaseObject>();

	return children[index];
}

size_t BaseObject::GetChildCount()
{
	return children.size();
}

void BaseObject::Update(float dt)
{
	for (auto& i : components)
	{
		auto& c = i.second;
		if (!c->GetEnabled()) return;

		i.second->Update(dt);
	}

	for (auto& c : children)
	{
		c->Update(dt);
	}
}

void BaseObject::SetTransformChanged()
{
	isTransformChanged = true;

	for (auto& c : components)
		c.second->transformChanged = true;

	// Set it's children's transform changed recursively
	for (auto& c : children)
		c->SetTransformChanged();
}

void BaseObject::RecalculateTransform()
{
	isTransformChanged = false;

	// For top object
	if (parent.expired())
	{
		worldTransform = localTransform = glm::mat4(1);
		return;
	}

	const auto& scaled = glm::scale(glm::mat4(1), localScale);
	const auto& rotated = glm::mat4(localRotation) * scaled;
	const auto& translated = glm::translate(glm::mat4(1), localPosition) * rotated;

	localTransform = translated;

	worldTransform = parent.lock()->GetWorldTransform() * localTransform;
}

const glm::vec3& BaseObject::GetLocalPosition()
{
	return localPosition;
}

const glm::mat4& BaseObject::GetWorldTransform()
{
	if (isTransformChanged)
		RecalculateTransform();

	return worldTransform;
}

const glm::vec3 BaseObject::GetWorldPosition()
{
	return GetWorldTransform()[3];
}

void BaseObject::SetLocalPosition(glm::vec3 pos)
{
	localPosition = pos;

	SetTransformChanged();
}

void BaseObject::SetLocalPosition(float x, float y, float z)
{
	SetLocalPosition(glm::vec3(x, y, z));
}

void BaseObject::Translate(glm::vec3 vec)
{
	localPosition += glm::vec3(glm::mat4(localRotation) * glm::vec4(vec[0], vec[1], vec[2], 1));

	SetTransformChanged();
}

void BaseObject::Translate(float x, float y, float z)
{
	Translate(glm::vec3(x, y, z));
}

void BaseObject::RotateAxis(glm::vec3 axis, float rad)
{
	localRotation = glm::rotate(localRotation, rad, axis);

	SetTransformChanged();
}

void BaseObject::RotateAxis(float x, float y, float z, float rad)
{
	RotateAxis(glm::vec3(x, y, z), rad);
}

void BaseObject::SetScale(glm::vec3 scale)
{
	localScale = scale;

	SetTransformChanged();
}

void BaseObject::SetScale(float x, float y, float z)
{
	SetScale(glm::vec3(x, y, z));
}

void BaseObject::LookAt(glm::vec3 to)
{
	localRotation = glm::conjugate(glm::quat(glm::lookAtLH(GetWorldPosition(), to, glm::vec3(0, 1, 0))));

	SetTransformChanged();
}

void BaseObject::LookAt(float x, float y, float z)
{
	LookAt(glm::vec3(x, y, z));
}
