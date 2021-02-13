#ifndef GAMESCENE_H
#define GAMESCENE_H

#include"../GameEngine/Engine/Core/MEngine.h"
class GameScene: public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;
};

#endif // !GAMESCENE_H
