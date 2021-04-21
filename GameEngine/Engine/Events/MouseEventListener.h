#ifndef MOUSEEVENTLISTENER_H
#define MOUSEEVENTLISTENER_H


#include<SDL.h>
#include<glm/glm.hpp>
#include "../Core/MEngine.h"
class MEngine;
class MouseEventListener
{
public:
	MouseEventListener(const MouseEventListener&) = delete;
	MouseEventListener(MouseEventListener&&) = delete;
	MouseEventListener& operator=(const MouseEventListener&) = delete;
	MouseEventListener& operator=(MouseEventListener&&) = delete;

	MouseEventListener() = delete;
	~MouseEventListener();


	static void RegisterEngineObject(MEngine* engine_);
	static void Update(SDL_Event e_);

	static void NotifyOfMousePressed(int buttonType_);
	static void NotifyOfMouseReleased(int buttonType_);
	static void NotifyOfMouseMove();
	static void NotifyOfMouseScroll(int y_);

	static glm::vec2 GetPreviousMousePosition();
	static glm::vec2 GetMousePosition();
	static glm::vec2 GetMouseOffset();
private:
	static MEngine* engineInstance;
	static glm::vec2 mouse, prevMouse;
	static bool firstUpdate;
	static void UpdateMousePosition();
};

#endif