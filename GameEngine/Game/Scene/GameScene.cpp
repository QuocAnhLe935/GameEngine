#include "GameScene.h"

GameScene::GameScene(): shape(nullptr)
{
}

GameScene::~GameScene()
{
	model = nullptr;
	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate()
{

	Debug::Info("Create game scene", "GameScene.cpp", __LINE__);

	//Create verticles for triangle
	//
	Vertex v;
	std::vector<Vertex> vertexList;
	//reserve(doesn't have to move in the actual vector in the memory)
	vertexList.reserve(3);

	/*v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	v.color = glm::vec3(1.0f, 0.0f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.0f);
	v.color = glm::vec3(0.0f, 1.0f, 0.0f);
	vertexList.push_back(v);
	
	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	v.color = glm::vec3(0.0f, 0.0f, 1.0f);
	vertexList.push_back(v);*/



	v.position = glm::vec3(0.5f, 0.5f, 0.0f);
	v.color = glm::vec3(0.0f, 1.0f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	v.color = glm::vec3(1.0f, 0.0f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	v.color = glm::vec3(0.0f, 0.0f, 1.0f);
	vertexList.push_back(v);

	
	model = new Model(ShaderHandler::GetInstance()->GetShader("colorShader"));
	//create new mesh pass in vertexlist
	//get 3 meshes verticle to Mesh contructor 
	//then pass entire mesh object to model
	model->AddMesh(new Mesh(vertexList, ShaderHandler::GetInstance()->GetShader("colorShader")));
	model->SetScale(glm::vec3(0.5f));

	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_)
{
	model->SetAngle(model->GetAngle() + 0.05f);
}

void GameScene::Render()
{
	shape->Render();
	Debug::Info("Triangle", "GameScene.cpp", __LINE__);
}
