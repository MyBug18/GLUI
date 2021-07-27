#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "App.h"
#include "Hierarchy.h"
#include "WindowHolder.h"

std::unique_ptr<App> App::instance = std::make_unique<App>();

App::App()
{
	hierarchy = std::make_unique<Hierarchy>();
	windowHolder = std::make_unique<WindowHolder>();
	timeStamp = 0;
}

void App::Initialize()
{
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	windowHolder->InitWindow(1280, 720);

	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	hierarchy->Initialize();
	timeStamp = (float)glfwGetTime();
}

App::~App()
{
}

App* App::Instance()
{
	return instance.get();
}

Hierarchy* App::GetHierarchy()
{
	return hierarchy.get();
}

WindowHolder* App::GetWindowHolder()
{
	return windowHolder.get();
}

bool App::ShouldClose()
{
	return windowHolder->ShouldClose();
}

void App::Update()
{
	auto now = (float)glfwGetTime();
	auto dt = now - timeStamp;
	timeStamp = now;

	hierarchy->Update(dt);
	hierarchy->Render();
	hierarchy->AfterLoop();
	windowHolder->SwapBuffers();
	glfwPollEvents();
}
