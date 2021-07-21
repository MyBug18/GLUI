#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "BaseObject.h"

class Camera
{
private:
	int priority;
	std::weak_ptr<BaseObject> cameraHolder;

	glm::mat4 viewMatrix;
protected:
	glm::mat4 projectionMatrix;
	bool isProjectionChanged = true;
public:
	Camera(std::weak_ptr<BaseObject> h);
	virtual ~Camera();

	static const std::vector<Camera*>& GetCameras();

	const glm::mat4& GetViewMatrix();
	virtual const glm::mat4& GetProjectionMatrix() = 0;

	virtual void OnResizeWindow(int, int) = 0;

	void SetPriority(int);
	int GetPriority();
};
