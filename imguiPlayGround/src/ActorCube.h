#pragma once
#include "Actor.h"
#include <fbxsdk.h>
#include <map>
#include <string>

class ActorCube : public Actor
{
public:
	ActorCube(std::weak_ptr<Scene> scene, const std::string& fbxFilePath);
	~ActorCube();
	void update() final;
	void draw() final;

private:
	GLuint coordinateBuffer_;
	glm::mat4 modelMat4_;
	glm::mat4 mvpMat4_;
	float yaw_;
	float pitch_;
	int numOfPoints_;

	void CollectMeshNode(FbxNode* node, std::map<std::string, FbxNode*>& list);
};