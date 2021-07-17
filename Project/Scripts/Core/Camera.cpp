#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include "Camera.h"
#include "App.h"

bool Camera::CompareCameraPriority(std::weak_ptr<Camera> x, std::weak_ptr<Camera> y)
{
	return x.lock()->priority < y.lock()->priority;
}

const std::vector<std::weak_ptr<Camera>>& Camera::GetCameras()
{
	return cameras;
}

Camera::Camera(std::weak_ptr<BaseObject> holder) : TypedComponent<Camera>(holder)
{
	priority = 0;

	fov = 1.0472f;
	near = 0.1f;
	far = 1000.0f;
	aspect = App::Instance()->GetWindowHolder()->GetAspect();
	perspectiveMatrix = glm::perspectiveLH(fov, aspect, near, far);

	auto h = holder.lock();

	viewMatrix = glm::inverse(h->GetWorldTransform());
	pvMatrix = perspectiveMatrix * viewMatrix;
}

Camera::~Camera()
{
}

const glm::mat4& Camera::GetProjectionMatrix()
{
	return perspectiveMatrix;
}

const glm::mat4& Camera::GetViewMatrix()
{
	if (transformChanged)
		RecalculateTransform();

	return viewMatrix;
}

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

void Camera::SetPriority(int p)
{
	priority = p;
	std::sort(cameras.begin(), cameras.end(), Camera::CompareCameraPriority);
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
