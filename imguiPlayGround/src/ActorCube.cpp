#include "ActorCube.h"
#include "GLSLManager.h"
#include "GLSLPassthrough.h"
#include "Scene.h"
#include "WindowMain.h"
#include <array>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include <vector>

ActorCube::ActorCube(std::weak_ptr<Scene> scene)
	: Actor(scene)
	, yaw_(0.0f)
	, pitch_(0.0f)
{
	modelMat4_ = glm::mat4(1.0f);
	mvpMat4_ = glm::mat4(1.0f);

	FbxManager* fbxManager = FbxManager::Create();
	if (fbxManager == nullptr)
	{
		std::cerr << "Failed to create FbxManager!!" << std::endl;
		exit(1);
	}

	FbxImporter* fbxImporter = FbxImporter::Create(fbxManager, "Import");
	if (fbxImporter == nullptr)
	{
		fbxManager->Destroy();

		std::cerr << "Failed to create FbxImporter!!" << std::endl;
		exit(1);
	}

	FbxScene* fbxScene = FbxScene::Create(fbxManager, "Scene");
	if (fbxScene == nullptr)
	{
		fbxImporter->Destroy();
		fbxManager->Destroy();

		std::cerr << "Failed to create FbxScene!!" << std::endl;
		exit(1);
	}

	if (fbxImporter->Initialize("resource\\cube.fbx") == false)
	{
		fbxImporter->Destroy();
		fbxScene->Destroy();
		fbxManager->Destroy();

		std::cerr << "Failed to FbxImporter Initialize!!" << std::endl;
		exit(1);
	}

	if (fbxImporter->Import(fbxScene) == false)
	{
		fbxImporter->Destroy();
		fbxScene->Destroy();
		fbxManager->Destroy();

		std::cerr << "Failed to FbxImporter Import!!" << std::endl;
		exit(1);
	}

	FbxGeometryConverter converter(fbxManager);
	converter.Triangulate(fbxScene, true);

	std::map<std::string, FbxNode*> meshNodeList;
	CollectMeshNode(fbxScene->GetRootNode(), meshNodeList);

	std::vector<float> coordinates;
	for (auto& i : meshNodeList)
	{
		FbxNode* node = i.second;
		FbxMesh* mesh = node->GetMesh();
		FbxVector4* vertices = mesh->GetControlPoints();
		int* indices = mesh->GetPolygonVertices();
		int polygonVertexCount = mesh->GetPolygonVertexCount();
		for (int i = 0; i < polygonVertexCount; i++)
		{
			int index = indices[i];
			coordinates.push_back(vertices[index][0]);
			coordinates.push_back(vertices[index][1]);
			coordinates.push_back(vertices[index][2]);
		}
	}

	numOfPoints_ = coordinates.size() / 3;
	glGenBuffers(1, &coordinateBuffer_);
	glBindBuffer(GL_ARRAY_BUFFER, coordinateBuffer_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * coordinates.size(), coordinates.data(), GL_STATIC_DRAW);

	if (fbxImporter != nullptr)
	{
		fbxImporter->Destroy();
	}

	if (fbxScene != nullptr)
	{
		fbxScene->Destroy();
	}

	if (fbxManager != nullptr)
	{
		fbxManager->Destroy();
	}
}

ActorCube::~ActorCube()
{
	glDeleteBuffers(1, &coordinateBuffer_);
	coordinateBuffer_ = 0;
}

void ActorCube::update()
{
	WindowMain& windowMain = WindowMain::getInstance();
	if (windowMain.pressMouseButtonRight())
	{
		const glm::vec2 delta = (windowMain.curMousePos() - windowMain.prevMousePos()) * 0.004f;
		const glm::vec3 cUp = {0.0f, 1.0f, 0.0f};
		float sign = glm::rotate(glm::quat(glm::vec3(-pitch_, -yaw_, 0.0f)), cUp).y < 0 ? -1.0f : 1.0f;
		yaw_ += sign * delta.x;
		pitch_ += delta.y;
	}

	modelMat4_ = glm::toMat4(glm::quat(glm::vec3(-pitch_, -yaw_, 0.0f)));
	modelMat4_ = glm::inverse(modelMat4_);
	modelMat4_ = glm::scale(modelMat4_, glm::vec3(50.0f, 50.0f, 50.0f));
	std::shared_ptr<Scene> scene = scene_.lock();
	mvpMat4_ = scene->getProjMat4() * scene->getViewMat4() * modelMat4_;
}

void ActorCube::draw()
{
	glEnable(GL_DEPTH_TEST);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, coordinateBuffer_);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	const GLSLPassthrough& glslPassthrough = static_cast<const GLSLPassthrough&>(GLSLManager::getInstance().getGLSL(GLSLType::passthrough));
	glslPassthrough.setMVP(mvpMat4_);

	glUseProgram(glslPassthrough.getProgram());
	glLineWidth(5.0f);
	glPointSize(10.0f);
	glm::vec4 color(1.0f, 1.0f, 0.0f, 1.0f);
	glslPassthrough.setOutputColor(color);
	glDrawArrays(GL_TRIANGLES, 0, numOfPoints_);
	glUseProgram(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
}

void ActorCube::CollectMeshNode(FbxNode* node, std::map<std::string, FbxNode*>& list)
{
	for (int i = 0; i < node->GetNodeAttributeCount(); i++)
	{
		FbxNodeAttribute* attribute = node->GetNodeAttributeByIndex(i);
		if (attribute->GetAttributeType() == FbxNodeAttribute::EType::eMesh)
		{
			list[node->GetName()] = node;
			break;
		}
	}

	for (int i = 0; i < node->GetChildCount(); i++)
	{
		this->CollectMeshNode(node->GetChild(i), list);
	}
}