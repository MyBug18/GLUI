#include "PerspectiveCamera.h"
#include "../Core/App.h"
#include "../Core/WindowHolder.h"

PerspectiveCamera::PerspectiveCamera(std::weak_ptr<BaseObject> holder) : TypedComponent<PerspectiveCamera>(holder), Camera(holder)
{
	fov = 1.04f;
	aspect = App::Instance()->GetWindowHolder()->GetAspect();
	near = 0.1f;
	far = 1000;
}

PerspectiveCamera::~PerspectiveCamera()
{
}

const glm::mat4& PerspectiveCamera::GetProjectionMatrix()
{
	if (isProjectionChanged)
		projectionMatrix = glm::perspectiveLH(fov, aspect, near, far);

	return projectionMatrix;
}

void PerspectiveCamera::OnResizeWindow(int w, int h)
{
	aspect = (float)w / h;
}
