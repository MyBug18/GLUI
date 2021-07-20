#pragma once

#include "../Core/Camera.h"
#include "../Core/Component.h"

class OrthographicCamera : public TypedComponent<OrthographicCamera>, public Camera
{
private:
	float width;
	float height;
public:
	OrthographicCamera(std::weak_ptr<BaseObject>);
	~OrthographicCamera();

	const glm::mat4& GetProjectionMatrix() override;
};

template <>
inline std::string GetTypeName<OrthographicCamera>()
{
	return "OrthographicCamera";
}
