#include "Engine/Core/MEngine.h"



int main(int argc, char* argv[]) {
	
	if (!MEngine::GetInstance()->OnCreate("Game 256", 800, 600)) {
		printf("Engine failed to initialize");
		
		exit(0);
	}

	MEngine::GetInstance()->Run();
	exit(0);
}