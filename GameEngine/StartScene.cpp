#include "StartScene.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	printf("HI from startscene");
	Debug::Info("START SECEN 0", "StartScene.cpp", __LINE__);
	return true;
}

void StartScene::Update(const float deltaTime_)
{
}

void StartScene::Render()
{
}
