#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "Scripts/Core/App.h"
#include "Scripts/Components/RandomMesh.h"
#include "Scripts/Components/SquareMesh.h"

int main(void)
{
	auto app = App::Instance();
	app->Initialize();

	auto top = app->GetHierarchy()->GetTopObject();

	auto childDepth1 = top->Instantiate().lock();

	// auto mesh1 = childDepth1->AddComponent<RandomMesh>().lock();
	// mesh1->SetVerticeData("l 10");
	auto mesh1 = childDepth1->AddComponent<SquareMesh>().lock();
	mesh1->SetSquareData(-100, -100, 100, 100);

	while (!app->ShouldClose())
	{
		app->Update();
	}

	App::Instance()->GetWindowHolder()->DestroyWindow();
	glfwTerminate();
	exit(EXIT_SUCCESS);

	return 1;
}
