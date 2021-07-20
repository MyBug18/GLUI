#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(std::weak_ptr<BaseObject> holder) : TypedComponent<OrthographicCamera>(holder), Camera(holder)
{
	width = App::Instance()->GetWindowHolder()->GetWidth();
	height = App::Instance()->GetWindowHolder()->GetHeight();
}

OrthographicCamera::~OrthographicCamera()
{
}

const glm::mat4& OrthographicCamera::GetProjectionMatrix()
{
	if (isProjectionChanged)
		projectionMatrix = glm::orthoLH<float>(-width / 2, width / 2, -height / 2, height / 2, 0.1f, 1000);

	return projectionMatrix;
}
