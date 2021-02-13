#ifndef  GAME0_H
#define GAME0_H

#include "../Engine/Core/MEngine.h"
#include "../StartScene.h"
#include "../GameScene.h"
class Game0: public GameMainFrame
{
public:
	Game0();
	virtual ~Game0();


	//override it will check the child need to be the same as parent class
	//ex, update int? no, const float
	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;

private:

	int currentSceneNum;
	Scene* currentScene;
	void BuildScene();
};

#endif // ! GAME0_H