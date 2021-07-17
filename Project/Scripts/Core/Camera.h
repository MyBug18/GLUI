#pragma once

#include <glm/glm.hpp>
#include <functional>
#include <memory>
#include "Component.h"

class Camera : public TypedComponent<Camera>
{
private:
	inline static std::vector<std::weak_ptr<Camera>> cameras;
	static bool CompareCameraPriority(std::weak_ptr<Camera>, std::weak_ptr<Camera>);

	int priority;

	float fov;
	float near;
	float far;
	float aspect;

	glm::mat4 viewMatrix;
	glm::mat4 perspectiveMatrix;

	glm::mat4 pvMatrix;

	void RecalculateTransform();

	void Start() override;
	void Update(float dt) override;
public:
	Camera(std::weak_ptr<BaseObject>);
	~Camera();

	static const std::vector<std::weak_ptr<Camera>>& GetCameras();

	const glm::mat4& GetViewMatrix();
	const glm::mat4& GetProjectionMatrix();
	const glm::mat4& GetPVMatrix();

	/// <summary>
	/// Change the camera's render priority. Changed priority will be applied on the next frame.
	/// </summary>
	void SetPriority(int);
};

template <>
inline std::string GetTypeName<Camera>()
{
	return "Camera";
}
