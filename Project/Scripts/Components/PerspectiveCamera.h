#pragma once

#include "../Core/Camera.h"
#include "../Core/Component.h"

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
};

template <>
inline std::string GetTypeName<PerspectiveCamera>()
{
	return "PerspectiveCamera";
}
