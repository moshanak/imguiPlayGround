#include "Actor.h"

Actor::Actor(std::weak_ptr<Scene> scene)
	: scene_(scene)
{
}

Actor::~Actor()
{
}
