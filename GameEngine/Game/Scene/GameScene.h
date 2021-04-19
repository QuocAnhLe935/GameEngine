#ifndef GAMESCENE_H
#define GAMESCENE_H


#include "../../Engine/Core/MEngine.h"
class GameScene: public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;
private:
	/*GameObject* shape;
	Model* model;*/
	LightSource* light;
};

#endif // !GAMESCENE_H
