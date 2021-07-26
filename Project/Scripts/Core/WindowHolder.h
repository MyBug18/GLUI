#pragma once

#include <functional>

struct GLFWwindow;

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

	void RegisterWindowResizeCallback(unsigned long, std::function<void(int, int)>);
	void RemoveWindowResizeCallback(unsigned long);

	int GetWidth();
	int GetHeight();
	float GetAspect();

	GLFWwindow* GetRawPointer();
};
