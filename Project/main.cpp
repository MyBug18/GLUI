#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "Scripts/Core/App.h"
#include "Scripts/Core/Hierarchy.h"
#include "Scripts/Core/WindowHolder.h"
#include "Scripts/Components/RandomMesh.h"
#include "Scripts/Components/SquareMesh.h"
#include "Scripts/Components/PerspectiveCamera.h"
#include "Scripts/Components/OrthographicCamera.h"

int main(void)
{
	auto app = App::Instance();
	app->Initialize();

	auto top = app->GetHierarchy()->GetTopObject();

	auto cameraHolder = top->Instantiate().lock();
	//cameraHolder->AddComponent<PerspectiveCamera>();
	cameraHolder->AddComponent<OrthographicCamera>();
	cameraHolder->SetLocalPosition(glm::vec3(0, 0, -5));

	auto childDepth1 = top->Instantiate().lock();
	childDepth1->SetScale(360, 360, 360);

	// auto mesh1 = childDepth1->AddComponent<RandomMesh>().lock();
	// mesh1->SetVerticeData("l 10");
	auto mesh1 = childDepth1->AddComponent<SquareMesh>().lock();
	mesh1->SetSquareData(-1, -1, 1, 1);

	while (!app->ShouldClose())
	{
		app->Update();
	}

	App::Instance()->GetWindowHolder()->DestroyWindow();
	glfwTerminate();
	exit(EXIT_SUCCESS);

	return 1;
}
