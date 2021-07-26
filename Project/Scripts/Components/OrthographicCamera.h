#pragma once

#include "../Core/Component.h"
#include "../Core/Camera.h"

class OrthographicCamera : public TypedComponent<OrthographicCamera>, public Camera
{
private:
	int width;
	int height;
public:
	OrthographicCamera(std::weak_ptr<BaseObject>);
	~OrthographicCamera();

	const glm::mat4& GetProjectionMatrix() override;
	void OnResizeWindow(int, int) override;
};

template <>
inline std::string GetTypeName<OrthographicCamera>()
{
	return "OrthographicCamera";
}
