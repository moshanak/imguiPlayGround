#include "Scene.h"
#include "ActorBackground.h"
#include "ActorCoordinateAxis.h"
#include "ActorCube.h"
#include "WindowMain.h"
#include <GL/glew.h>

Scene::Scene()
{
}

void Scene::init()
{
	viewMat4_ = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	updateProjMat4();
	actors_.emplace_back(std::make_shared<ActorBackground>(weak_from_this()));
	// actors_.emplace_back(std::make_shared<ActorCube>(weak_from_this(), "resource\\cube.fbx"));
	actors_.emplace_back(std::make_shared<ActorCube>(weak_from_this(), "resource\\sphere.fbx"));
	actors_.emplace_back(std::make_shared<ActorCoordinateAxis>(weak_from_this()));
}

void Scene::update()
{
	updateProjMat4();
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

void Scene::updateProjMat4()
{
	const WindowMain& windowMain = WindowMain::getInstance();
	// projMat4_ = glm::perspective(glm::radians(45.f), 1.33f, 0.1f, 10.f);
	const float halfWidth = 0.5f * static_cast<float>(windowMain.width());
	const float halfHeight = 0.5f * static_cast<float>(windowMain.height());
	projMat4_ = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -100.0f, 100.0f);
}
