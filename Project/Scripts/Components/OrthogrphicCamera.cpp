#include "OrthographicCamera.h"
#include "../Core/App.h"
#include "../Core/WindowHolder.h"

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
		projectionMatrix = glm::orthoLH<float>(-w / 2, w / 2, -h / 2, h / 2, -1000, 1000);
		auto a = static_cast<float>(5);
	}

	return projectionMatrix;
}

void OrthographicCamera::OnResizeWindow(int w, int h)
{
	width = w;
	height = h;
}
