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
	cameraHolder->AddComponent<OrthographicCamera>();
	cameraHolder->SetLocalPosition(glm::vec3(0, 0, -5));

	auto child1 = top->Instantiate().lock();
	child1->SetScale(360, 360, 360);
	child1->AddComponent<RandomMesh>().lock()->SetVerticeData("l 15");

	auto child2 = top->Instantiate().lock();
	child2->SetScale(180, 180, 180);
	child2->AddComponent<SquareMesh>().lock()->SetSquareData(-1, -1, 1, 1);

	while (!app->ShouldClose())
	{
		app->Update();
	}

	App::Instance()->GetWindowHolder()->DestroyWindow();
	glfwTerminate();
	exit(EXIT_SUCCESS);

	return 1;
}
