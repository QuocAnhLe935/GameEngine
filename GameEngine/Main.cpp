#include "Window.h"


Window* window;

int main(int argc, char* argv[]) {
	 window = new Window();
	if (!window->OnCreate("GAME", 800, 600)) {
		printf("failed to create window");
		delete window;
		window = nullptr;
		return 0;
	}

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SDL_GL_SwapWindow(window->GetWindow());
	SDL_Delay(5000);
	delete window;
	window = nullptr;
	return 0;
}