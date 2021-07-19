#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include "Camera.h"
#include "App.h"

std::vector<Camera*> cameras;

bool CompareCameraPriority(Camera* x, Camera* y)
{
	return x->GetPriority() < y->GetPriority();
}

const std::vector<Camera*>& Camera::GetCameras()
{
	return cameras;
}

Camera::Camera(std::weak_ptr<BaseObject> holder)
{
	priority = 0;
	this->holder = holder;

	auto h = holder.lock();
	holderId = h->GetId();
	viewMatrix = glm::inverse(h->GetWorldTransform());

	App::Instance()->GetHierarchy()->RegisterAfterLoopCallback([this]()
		{
			cameras.push_back(this);
			std::sort(cameras.begin(), cameras.end(), CompareCameraPriority);
		});
}

Camera::~Camera()
{
	for (auto i = 0; i < cameras.size(); i++)
	{
		const auto& c = cameras[i];
		if (holderId != c->holderId)
			continue;

		cameras.erase(cameras.begin() + i);
		break;
	}
}

const glm::mat4& Camera::GetViewMatrix()
{
	auto h = holder.lock();
	if (holder.lock()->IsTransformChanged())
	{
		viewMatrix = glm::inverse(h->GetWorldTransform());
	}

	return viewMatrix;
}

void Camera::SetPriority(int p)
{
	priority = p;
}

int Camera::GetPriority()
{
	return priority;
}

/*
void Camera::Start()
{
	cameras.push_back(GetSelfReference());

	for (auto i = (int)cameras.size() - 1; i >= 0; i--)
	{
		if (cameras[i].expired())
			cameras.erase(cameras.begin() + i);
	}

	std::sort(cameras.begin(), cameras.end(), Camera::CompareCameraPriority);
}

void Camera::Update(float dt)
{
	int front = 0, right = 0;
	const auto& w = App::Instance()->GetWindowHolder()->GetRawPointer();
	front += glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS ? 1 : 0;
	front += glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS ? -1 : 0;
	right += glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS ? 1 : 0;
	right += glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS ? -1 : 0;
	holder.lock()->Translate(right * dt * 2, 0, front * dt * 2);

	if (glfwGetKey(w, GLFW_KEY_X) == GLFW_PRESS)
		holder.lock()->LookAt(0, 0, 0);
}

void Camera::RecalculateTransform()
{
	transformChanged = false;

	auto h = holder.lock();

	viewMatrix = glm::inverse(h->GetWorldTransform());
	pvMatrix = perspectiveMatrix * viewMatrix;
}

const glm::mat4& Camera::GetPVMatrix()
{
	if (transformChanged)
		RecalculateTransform();

	return pvMatrix;
}
*/
