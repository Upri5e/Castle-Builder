#pragma once

#include "SDL.h"
#include "Game.h"
#include <vector>

enum MouseButton{LEFT, RIGHT};
class Input
{
public:
	static Input* GetInstance() {
		return instance = (instance != nullptr) ? instance : new Input();
	}
	void Listen(Game* game);
	bool GetMouseButtonDown(MouseButton button) { return mouseButtonState[button]; }

private:
	Input();

	const Uint8* keyState;
	static Input* instance;

	std::vector<bool> mouseButtonState = {false, false};
	void MouseMotion(SDL_Event event);
	void MouseUp(SDL_Event event);
	void MouseDown(SDL_Event event);
};