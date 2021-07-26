#include <unordered_map>
#include "WindowHolder.h"

std::unordered_map<unsigned long, std::function<void(int, int)>> windowResizeCallbacks;

void CallWindowResizeCallbacks(GLFWwindow*, int w, int h)
{
	glViewport(0, 0, w, h);
	for (auto& f : windowResizeCallbacks)
		f.second(w, h);
}

WindowHolder::WindowHolder()
{
	width = 0;
	height = 0;
	window = nullptr;
}

WindowHolder::~WindowHolder()
{
	window = nullptr;
}

void WindowHolder::InitWindow(int w, int h)
{
	width = w;
	height = h;

	window = glfwCreateWindow(w, h, "yeah", NULL, NULL);
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, CallWindowResizeCallbacks);
}

bool WindowHolder::ShouldClose()
{
	return glfwWindowShouldClose(window);
}

void WindowHolder::SwapBuffers()
{
	glfwSwapBuffers(window);
}

void WindowHolder::DestroyWindow()
{
	glfwDestroyWindow(window);
}

void WindowHolder::RegisterWindowResizeCallback(unsigned long key, std::function<void(int, int)> f)
{
	windowResizeCallbacks[key] = f;
}

void WindowHolder::RemoveWindowResizeCallback(unsigned long key)
{
	windowResizeCallbacks.erase(key);
}

int WindowHolder::GetWidth()
{
	return width;
}

int WindowHolder::GetHeight()
{
	return height;
}

float WindowHolder::GetAspect()
{
	return (float)width / height;
}

GLFWwindow* WindowHolder::GetRawPointer()
{
	return window;
}
