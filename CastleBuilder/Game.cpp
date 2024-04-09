#include "Game.h"
#include "TextureManager.h"
#include <string>
#include "GUI/Widget.h"
#include "pugi/pugixml.hpp"

SDL_Rect mapSrc, mapDest;

int Game::playAreaWidth = 800;
int Game::playAreaHeight = 640;
ECS_Manager Game::manager;

SDL_Window* Game::window = nullptr;
SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) //0 success -1 error
	{
		std::cout << "Subsystems Initialised!..." << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0); //-1 for first renderer
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;

		//Initialize the widget
		Widget::GetInstance()->Init(renderer, window);
	}

}

void Game::Update()
{
	manager.Refresh(); //Always call refresh before update incase entities or components where removed
	manager.Update(); //Calls all entitys' updates
	Widget::GetInstance()->Update();
}

void Game::Render()
{
	SDL_RenderClear(renderer); //Not needed but I added it just incase
	//Add Stuff to the renderer
	Widget::GetInstance()->Draw(); //Should have separated the map so i can draw entities above map but under widgets
	manager.Draw(); //Draws all entities
	SDL_RenderPresent(renderer); //Renders the full "image" every frame
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;
}

void Game::SetPlayArea(int w, int h)
{
	playAreaWidth = w;
	playAreaHeight = h;
}
