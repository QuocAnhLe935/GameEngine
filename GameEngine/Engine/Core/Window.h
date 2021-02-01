#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>
//tset3
class Window
{
public:
	Window();
	~Window();
	bool OnCreate(std::string name_, int width_, int height_);
	void OnDestroy();
	//const at the end return normal int not const int a promise not to touch
	int GetWidth() const;
	int GetHeight() const;
	SDL_Window* GetWindow() const; //return sdlwindow

private:
	void SetPreAttributes();
	void SetPosAttributes();

	int width;
	int height;
	SDL_Window* window;
	//sdlopengl context like a door way to grpahic card comm
	SDL_GLContext context;
};

#endif // !WINDOW_H