#include "ActorBackground.h"
#include "WindowMain.h"

ActorBackground::ActorBackground(std::weak_ptr<Scene> scene)
	: Actor(scene)
{
}

ActorBackground::~ActorBackground()
{
}

void ActorBackground::update()
{
	WindowMain& windowMain = WindowMain::getInstance();
	const glm::vec3& color = windowMain.backgroundColor();
	glClearColor(color.r, color.g, color.b, 1.0f);
}

void ActorBackground::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
