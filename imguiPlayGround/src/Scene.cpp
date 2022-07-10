#include "Scene.h"
#include "ActorCoordinateAxis.h"
#include "WindowMain.h"
#include <GL/glew.h>

Scene::Scene()
{
	actors_.emplace_back(std::make_shared<ActorCoordinateAxis>());
}

void Scene::draw()
{
	const WindowMain& windowMain = WindowMain::getInstance();

	glViewport(0, 0, windowMain.getWidth(), windowMain.getHeight());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto& actor : actors_)
	{
		actor->draw();
	}
}
