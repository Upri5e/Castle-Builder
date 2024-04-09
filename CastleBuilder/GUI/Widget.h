#pragma once
#include "SDL.h"
#include "../Buildings.h"

class Widget
{
public:
	static Widget* GetInstance() {
		return instance = (instance != nullptr) ? instance : new Widget();
	}

	void Init(SDL_Renderer* renderer, SDL_Window* Window);

	void Update();
	void Draw();
	void EventHandle(SDL_Event event);

	void LoadShop();
	static void BuildingDeletePrompt(Button* button);
private:
	static Widget* instance;
	Widget();

	void InitDeletePrompt();
};

