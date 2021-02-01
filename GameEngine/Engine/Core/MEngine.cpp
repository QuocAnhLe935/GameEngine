#include "MEngine.h"

std::unique_ptr<MEngine> MEngine::engineInstance = nullptr;

MEngine::MEngine() :window(nullptr), isRunning(nullptr)
{
}

MEngine::~MEngine()
{
}
//calling whenever you want to access anything from this engine to PUBLIC
MEngine* MEngine::GetInstance()
{
	//check if instance has created BEFORE? 
	//If no, reset unique pointer wtiht new Mengine
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new MEngine);
	}
	return engineInstance.get();
}

bool MEngine::OnCreate(std::string name_, int width_, int height_)
{
	//make sure to call window pointer
	window = new Window();
	//Fail to create window send error-> engine is NOT running?
	if (!window->OnCreate(name_, width_, height_)) {
		std::cout << "Window failed to initialize" << std::endl;
		OnDestroy();
		return isRunning = false;
	}
	return isRunning = true;
}

void MEngine::Run()
{
	while (isRunning) {
		//run 60 fps
		Update(0.016f);
		Render();
	}
	if (!isRunning) {
		OnDestroy();
	}
}

bool MEngine::GetIsRunning()
{
	return isRunning;
}

void MEngine::Update(const float deltaTime_)
{
}

void MEngine::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//call game render
	SDL_GL_SwapWindow(window->GetWindow());
}

void MEngine::OnDestroy()
{
	delete window;
	SDL_Quit();
	exit(0);
}
