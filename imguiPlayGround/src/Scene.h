#pragma once
#include "Actor.h"
#include <memory>
#include <vector>

class Scene : public std::enable_shared_from_this<Scene>
{
public:
	Scene();
	void init();
	void update();
	void draw();

	const glm::mat4& getProjMat4() const { return projMat4_; }
	const glm::mat4& getViewMat4() const { return viewMat4_; }

private:
	std::vector<std::shared_ptr<Actor>> actors_;
	glm::mat4 projMat4_;
	glm::mat4 viewMat4_;

	void updateProjMat4();
};