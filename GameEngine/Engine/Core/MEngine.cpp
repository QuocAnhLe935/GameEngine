#include "MEngine.h"
//redeclare static varible
std::unique_ptr<MEngine> MEngine::engineInstance = nullptr;

MEngine::MEngine() :window(nullptr), isRunning(nullptr), fps(59), gameMainFrame(nullptr),
currentSceneNum(0), timer(nullptr)
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
	Debug::Oncreate();
	//make sure to call window pointer
	window = new Window();
	//Fail to create window send error-> engine is NOT running?
	if (!window->OnCreate(name_, width_, height_)) {
		
		Debug::FatalError("Windowfailed", "MEngine.cpp",__LINE__);
		
		OnDestroy();
		return isRunning = false;
	}
	//after window is created, pass instance sdl window
	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);

	MouseEventListener::RegisterEngineObject(this);

	ShaderHandler::GetInstance()->CreateProgram("colorShader",
		"Engine/Shaders/ColorVertexShader.glsl",
		"Engine/Shaders/ColorFragmentShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("basicShader",
		"Engine/Shaders/VertextShader.glsl",
		"Engine/Shaders/FragmentShader.glsl");
	//FragmentShader


	if (gameMainFrame) {
		if (!gameMainFrame->OnCreate()) {
			
			Debug::FatalError("GAME FAILED TO INITIALIZE", "MEngine.cpp", __LINE__);
			OnDestroy();
			return isRunning = false;
		}
	}



	Debug::Info("worked", __FILE__, __LINE__);
	timer = new Timer();
	timer->Start();
	return isRunning = true;
}

void MEngine::Run()
{
	while (isRunning) {

		//run 60 fps
		timer->UpdateFrameTicks();
		EventListener::Update();
		Update(timer->GetDeltaTime());
		Render();
		//set sleep time to sleep
		SDL_Delay(timer->GetSleepTime(fps));
	}
	//if (!isRunning) {
		OnDestroy();
	//}
}

void MEngine::Exit()
{
	isRunning = false;
}

float MEngine::GetScreenWidth() const
{
	//static cast because window width is int 
	return static_cast<float>(window->GetWidth());
}

float MEngine::GetScreenHeight() const
{
	return static_cast<float>(window->GetHeight());
}


bool MEngine::GetIsRunning() const
{
	return isRunning;
}

int MEngine::GetCurrentScene() const
{

	return currentSceneNum;
}

void MEngine::SetCurrentScene(int sceneNum_)
{
	currentSceneNum = sceneNum_;
}

void MEngine::SetGameMainFrame(GameMainFrame* gamemainframe_)
{
	gameMainFrame = gamemainframe_;
}

Camera* MEngine::GetCamera() const
{
	return camera;
}

void MEngine::SetCamera(Camera* camera_)
{
	camera = camera_;
}

void MEngine::NotifyOfMousePressed(glm::vec2 mouse_, int buttonType_)
{
}

void MEngine::NotifyOfMouseReleased(glm::vec2 mouse_, int buttonType_)
{
	CollisionHandler::GetInstance()->MouseUpdate(mouse_, buttonType_);
}

void MEngine::NotifyOfMouseMove(glm::vec2 mouse_)
{
	if (camera) {
		camera->ProcessMouseMovement(MouseEventListener::GetMouseOffset());
	}
}

void MEngine::NotifyOfMouseScroll(int y_)
{
	if (camera) {
		camera->ProcessMouseZoom(y_);
	}
}

void MEngine::Update(const float deltaTime_)
{
	if (gameMainFrame) {
		gameMainFrame->Update(deltaTime_);
		//std::cout << deltaTime_<< std::endl;
		
	}
}

void MEngine::Render()
{
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//call game render
	if (gameMainFrame) {
		gameMainFrame->Render();
		
	}
	SDL_GL_SwapWindow(window->GetWindow());
}

void MEngine::OnDestroy()
{
	ShaderHandler::GetInstance()->OnDestroy();
	TextureHandler::GetInstance()->OnDestroy();
	SceneGraph::GetInstance()->OnDestroy();
	MaterialHandler::GetInstance()->OnDestroy();
	CollisionHandler::GetInstance()->OnDestroy();

	delete timer;
	timer = nullptr;
	
	delete window;
	window = nullptr;

	delete gameMainFrame;
	gameMainFrame = nullptr;

	delete camera;
	camera = nullptr;

	
	
	SDL_Quit();
	exit(0);
}
