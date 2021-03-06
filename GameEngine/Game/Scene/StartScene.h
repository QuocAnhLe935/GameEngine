#ifndef STARTSCENE_H
#define STARTSCENE_H

//#include"../GameEngine/Engine/Core/MEngine.h"
#include "../../Engine/Core/MEngine.h"


class StartScene : public Scene
{
public:
	StartScene();
	virtual ~StartScene();

	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;

	MEngine* engine;
	Scene* currentScene;
	int currentScenenum;
};

#endif // ! STARTSCENE_H