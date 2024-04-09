#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "ECS/ECS.h"

class Game
{
private:
	int count = 0;

public:
	Game();
	~Game();

	void Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

	void Update();
	void Render();
	void Clean();

	static SDL_Window* window;
	static SDL_Renderer* renderer;

	static int playAreaWidth;
	static int playAreaHeight;


	bool isRunning = false;

	static ECS_Manager manager;

	static void SetPlayArea(int w, int h);
};

