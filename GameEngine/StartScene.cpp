#include "StartScene.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	
	while(MEngine::GetInstance()->GetCurrentScene()==0){ 
	
		
		MEngine::GetInstance()->SetCurrentScene(1);
		Debug::Info("SUCCESSFUL ", "StartScene.cpp", __LINE__);

	}

	
	return true;
}

void StartScene::Update(const float deltaTime_)
{
}

void StartScene::Render()
{
}
