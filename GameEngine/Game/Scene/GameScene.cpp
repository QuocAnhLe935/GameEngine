#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
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

	CollisionHandler::GetInstance()->OnCreate();
	MEngine::GetInstance()->GetCamera()->Addlight(light);
	
	Model* appleModel = new Model(ShaderHandler::GetInstance()->GetShader("basicShader"),"Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl");
	SceneGraph::GetInstance()->AddModel(appleModel);
	SceneGraph::GetInstance()->AddGameObject(new GameObject(appleModel, glm::vec3(1.3f, 0.0f, 0.0f)), "Apple");
	//shape = new GameObject(model);
	appleModel = nullptr;

	Model* diceModel = new Model(ShaderHandler::GetInstance()->GetShader("basicShader"), "Resources/Models/Dice.obj", "Resources/Materials/Dice.mtl");
	SceneGraph::GetInstance()->AddModel(diceModel);
	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(-2.0f, 0.0f, -2.0f)));
	diceModel = nullptr;
	return true;
}

void GameScene::Update(const float deltaTime_)
{
	SceneGraph::GetInstance()->Update(deltaTime_);
	
	
}

void GameScene::Render()
{
	SceneGraph::GetInstance()->Render(MEngine::GetInstance()->GetCamera());
	
}
