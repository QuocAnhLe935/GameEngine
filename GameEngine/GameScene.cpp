#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

bool GameScene::OnCreate()
{
	printf("Start game scene");
	return true;
}

void GameScene::Update(const float deltaTime_)
{
	Debug::Info(std::to_string(deltaTime_), "GameScene.h", __LINE__);
}

void GameScene::Render()
{
}
