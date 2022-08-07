#include "Scene.h"
#include "ActorBackground.h"
#include "ActorCamera.h"
#include "ActorCoordinateAxis.h"
#include "ActorFbx.h"
#include "ActorGrid.h"
#include "WindowMain.h"
#include <GL/glew.h>

Scene::Scene()
	: projMat4_(glm::mat4())
	, viewMat4_(glm::mat4())
{
}

void Scene::init()
{
	actors_.emplace_back(std::make_shared<ActorCamera>(weak_from_this()));
	actors_.emplace_back(std::make_shared<ActorBackground>(weak_from_this()));
	actors_.emplace_back(std::make_shared<ActorGrid>(weak_from_this()));
	actors_.emplace_back(std::make_shared<ActorFbx>(weak_from_this(), "resource\\sphere.fbx"));
	actors_.emplace_back(std::make_shared<ActorCoordinateAxis>(weak_from_this()));
}

void Scene::update()
{
	for (auto& actor : actors_)
	{
		actor->update();
	}
}

void Scene::draw()
{
	const WindowMain& windowMain = WindowMain::getInstance();
	glViewport(0, 0, windowMain.width(), windowMain.height());
	glClear(GL_DEPTH_BUFFER_BIT);

	for (auto& actor : actors_)
	{
		actor->draw();
	}
}
