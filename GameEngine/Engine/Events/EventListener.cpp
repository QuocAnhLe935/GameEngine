#include "EventListener.h"
#include "../Core/MEngine.h"
EventListener::~EventListener()
{
}

void EventListener::Update()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		if (sdlEvent.type == SDL_QUIT) {
			MEngine::GetInstance()->Exit();
		}
		switch (sdlEvent.type) {
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
			//update functin call type of mouse
			MouseEventListener::Update(sdlEvent);
			break;
		default:
			break;
		}
	}
}
