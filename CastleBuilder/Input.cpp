#include "Input.h"
#include "GUI/Widget.h"
Input* Input::instance = nullptr;
SDL_Event event;

Input::Input()
{
}

void Input::Listen(Game* game)
{
	if (SDL_WaitEvent(&event) != 0) 
	{
		switch (event.type)
		{
		case SDL_QUIT:
			game->isRunning = false;
		case SDL_MOUSEBUTTONDOWN:
			MouseDown(event);
			break;
		case SDL_MOUSEBUTTONUP:
			MouseUp(event);
			break;
		}
		Widget::GetInstance()->EventHandle(event);
	}
}


void Input::MouseMotion(SDL_Event event)
{
	
}

void Input::MouseUp(SDL_Event event) //Sets mouseup for corrisponding mouse buttons
{
	if (event.button.button == SDL_BUTTON_LEFT)
		mouseButtonState[0] = false;

	if (event.button.button == SDL_BUTTON_RIGHT)
		mouseButtonState[1] = false;
}

void Input::MouseDown(SDL_Event event) //Sets mousedown for corrisponding mouse buttons
{
	if (event.button.button == SDL_BUTTON_LEFT)
		mouseButtonState[0] = true;

	if (event.button.button == SDL_BUTTON_RIGHT)
		mouseButtonState[1] = true;
}
