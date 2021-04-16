#include "GameScene.h"

GameScene::GameScene(): shape(nullptr)
{
}

GameScene::~GameScene()
{
	delete model;
	model = nullptr;
	delete shape;
	shape = nullptr;
	
	light = nullptr;
	//light[1] = nullptr;

}

bool GameScene::OnCreate()
{

	Debug::Info("Create game scene", "GameScene.cpp", __LINE__);

	MEngine::GetInstance()->SetCamera(new Camera());


	MEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
	
	//LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
	light = new LightSource();
	//light[1] = new LightSource();

	/*1st LIGHT*/
	light->setPosition(glm::vec3(1.0f, 0.0f, 1.4f));
	light->setAmbient(0.1f);
	light->setDiffuse(0.8f);
	light->setSpecular(0.7f);
	light->setLightColor(glm::vec3(1.0f, 1.0f, 1.0f));

	///*2nd LIGHT*/
	//light[1]->setPosition(glm::vec3(1.0f, 0.0f, 1.4f));
	//light[1]->setAmbient(0.1f);
	//light[1]->setDiffuse(0.8f);
	//light[1]->setSpecular(0.7f);
	//light[1]->setLightColor(glm::vec3(2.0f, 1.0f, 2.0f));


	MEngine::GetInstance()->GetCamera()->Addlight(light);
	//MEngine::GetInstance()->GetCamera()->Addlight(light[1]);

	//TextureHandler::GetInstance()->CreateTexture("CheckerboardTexture", "./Resources/Textures/CheckerboardTexture.png");
	model = new Model(ShaderHandler::GetInstance()->GetShader("basicShader"), "Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl");


	//Create verticles for triangle
	//
	//Vertex v;
	//std::vector<Vertex> vertexList;
	//reserve(doesn't have to move in the actual vector in the memory)
	
	

//color
//	model = new Model(ShaderHandler::GetInstance()->GetShader("basicShader"), "", "");
	
	/*SubMesh subMesh;
	subMesh.vertexList = vertexList;
	subMesh.textureID = TextureHandler::GetInstance()->GetTexture("CheckerboardTexture");*/
	//	//create new mesh pass in vertexlist
	////get 3 meshes verticle to Mesh contructor 
	////then pass entire mesh object to model
	//model->AddMesh(new Mesh(subMesh, ShaderHandler::GetInstance()->GetShader("basicShader")));
	////model->SetScale(glm::vec3(0.5f));

	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_)
{
	shape->Update(deltaTime_);
	
	
}

void GameScene::Render()
{
	shape->Render(MEngine::GetInstance()->GetCamera());
	
}
