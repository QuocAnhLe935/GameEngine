#include "Engine/Core/MEngine.h"
#include "Game/Game0.h"


int main(int argc, char* argv[]) {
	MEngine::GetInstance()->SetGameMainFrame(new Game0);


	if (!MEngine::GetInstance()->OnCreate("Game 256", 800, 600)) {
		
		Debug::FatalError("ENGINE FAILED TO INITIALIZED", "Main.cpp", __LINE__);
		exit(0);
	}
	//
	MEngine::GetInstance()->Run();
	exit(0);
}