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

	MEngine::GetInstance()->SetCamera(new Camera());
	MEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));


	//Create verticles for triangle
	//
	Vertex v;
	std::vector<Vertex> vertexList;
	//reserve(doesn't have to move in the actual vector in the memory)
	vertexList.reserve(6);

	v.position = glm::vec3(-0.5f, 0.5f, 1.0f);
	v.color = glm::vec3(1.0f, 0.0f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.0f);
	v.color = glm::vec3(0.0f, 1.0f, 0.0f);
	vertexList.push_back(v);
	
	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	v.color = glm::vec3(0.0f, 0.0f, 1.0f);
	vertexList.push_back(v);



	v.position = glm::vec3(0.5f, 0.5f, 0.0f);
	v.color = glm::vec3(0.0f, 1.0f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 1.0f);
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
	model->SetScale(glm::vec3(0.005f));

	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_)
{
	model->SetAngle(model->GetAngle() + 0.05f);
	model->SetPosition(model->GetPosition() - 0.0005f);
	//model->SetScale(glm::vec3(1.5f));
	model->SetScale(model->GetScale() * 1.003f);
}

void GameScene::Render()
{
	shape->Render(MEngine::GetInstance()->GetCamera());
	Debug::Info("Triangle", "GameScene.cpp", __LINE__);
}
