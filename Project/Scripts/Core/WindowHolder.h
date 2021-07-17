#pragma once

#include <GLFW/glfw3.h>
#include <functional>

class WindowHolder
{
private:
	WindowHolder(const WindowHolder&) = delete;
	WindowHolder& operator=(const WindowHolder&) = delete;

	int width;
	int height;
	GLFWwindow* window;
public:
	WindowHolder();
	~WindowHolder();

	void InitWindow(int, int);
	bool ShouldClose();
	void SwapBuffers();
	void DestroyWindow();

	void RegisterWindowResizeCallback(int, std::function<void(int, int)>);

	int GetWidth();
	int GetHeight();
	float GetAspect();

	GLFWwindow* GetRawPointer();
};
