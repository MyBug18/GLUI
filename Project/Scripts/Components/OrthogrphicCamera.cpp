#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(std::weak_ptr<BaseObject> holder) : TypedComponent<OrthographicCamera>(holder), Camera(holder)
{
	auto w = App::Instance()->GetWindowHolder();
	width = w->GetWidth();
	height = w->GetHeight();
}

OrthographicCamera::~OrthographicCamera()
{
}

const glm::mat4& OrthographicCamera::GetProjectionMatrix()
{
	if (isProjectionChanged)
	{
		auto w = (float)width;
		auto h = (float)height;
		projectionMatrix = glm::orthoLH<float>(-w / 2, w / 2, -h / 2, h / 2, 0.1f, 1000);
	}

	return projectionMatrix;
}

void OrthographicCamera::OnResizeWindow(int w, int h)
{
	width = w;
	height = h;
}
