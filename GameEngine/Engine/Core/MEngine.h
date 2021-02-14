#ifndef MENGINE_H
#define MENGINE_H

#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameMainFrame.h"
#include "../../Scene.h"
#include <memory>

#include "../../GameObject.h"
class MEngine
{
public:
	//a copy of this class will get an error
	//disable copy or move 
	MEngine(const MEngine&) = delete;
	MEngine(MEngine&&) = delete;
	MEngine& operator=(const MEngine&) = delete;
	MEngine& operator=(MEngine&&) = delete;

	//return main Mengine pointer
	static MEngine* GetInstance();
	//Call on create function on Window
	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	void Exit();

	bool GetIsRunning() const;
	int GetCurrentScene() const;

	void SetCurrentScene(int sceneNum_);
	void SetGameMainFrame(GameMainFrame* gamemainframe_);

private:
	MEngine();
	~MEngine();
	//Update every frame
	void Update(const float deltaTime_);
	//Render stuffs function
	void Render();
	//Destroy
	void OnDestroy();

	//hold a pointer you specify. hold a pointer to this engine class
	//When the program end, the unique ptr goes out of scope
	static std::unique_ptr<MEngine> engineInstance;
	//specically how to delete itself
	friend std::default_delete<MEngine>;


	//window pointer
	Window* window;
	//check T/F if engine is running
	bool isRunning;
	Timer timer;
	unsigned int fps;


	GameMainFrame* gameMainFrame;
	int currentSceneNum;
};

#endif // !MENGINE