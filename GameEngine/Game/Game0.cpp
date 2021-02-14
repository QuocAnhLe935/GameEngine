#include "Game0.h"

Game0::Game0() : GameMainFrame(), currentSceneNum(0), currentScene(nullptr)
{

}

Game0::~Game0()
{
	delete currentScene;
	currentScene = nullptr;
}

bool Game0::OnCreate()
{
	if (MEngine::GetInstance()->GetCurrentScene() == 0) {
		currentScene = new StartScene();
		currentSceneNum = 0;
		//set up start scene
		return currentScene->OnCreate();
	}
	
	Debug::FatalError("ENGINE SCENE IS NOT INITIALIZED TO 0", "GAME0.CPP", __LINE__);

	return false;
}

void Game0::Update(const float deltaTime_)
{
	//every single ticks make sure the game current number = engine scene number
	if (currentSceneNum != MEngine::GetInstance()->GetCurrentScene()) {
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void Game0::Render()
{
	currentScene->Render();
}

void Game0::BuildScene()
{
	delete currentScene;
	currentScene = nullptr;
	printf("Hi from Game0 build");
	switch (MEngine::GetInstance()->GetCurrentScene())
	{
	case 1:
		currentScene = new GameScene();
		break;
	default: //case 0
		currentScene = new StartScene();
	}
	currentSceneNum = MEngine::GetInstance()->GetCurrentScene();
	if (!currentScene->OnCreate()) {
		Debug::Error("SCENE FAILED TO BE CREATED", "GAME0", __LINE__);
		
		MEngine::GetInstance()->Exit();
	}
}
