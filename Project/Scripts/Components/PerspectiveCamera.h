#pragma once

#include "../Core/Component.h"
#include "../Core/Camera.h"

class PerspectiveCamera : public TypedComponent<PerspectiveCamera>, public Camera
{
private:
	float fov;
	float aspect;
	float near;
	float far;
public:
	PerspectiveCamera(std::weak_ptr<BaseObject>);
	~PerspectiveCamera();

	const glm::mat4& GetProjectionMatrix() override;
	void OnResizeWindow(int, int) override;
};

template <>
inline std::string GetTypeName<PerspectiveCamera>()
{
	return "PerspectiveCamera";
}
