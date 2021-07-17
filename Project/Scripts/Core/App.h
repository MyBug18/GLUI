#pragma once

#include <memory>
#include "Hierarchy.h"
#include "WindowHolder.h"

class Hierarchy;

class App
{
private:
	App(const App&) = delete;
	App& operator=(const App&) = delete;
	static std::unique_ptr<App> instance;

	float timeStamp;

	std::unique_ptr<Hierarchy> hierarchy;
	std::unique_ptr<WindowHolder> windowHolder;
public:
	App();
	~App();

	static App* Instance();

	void Initialize();

	Hierarchy* GetHierarchy();
	WindowHolder* GetWindowHolder();

	bool ShouldClose();

	void Update();
};
