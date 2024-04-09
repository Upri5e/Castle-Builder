#include "Game.h"
#include "Input.h"

Game* game = nullptr;
int main(int argc, char* argv[]) 
{	
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime; //How long frames take in ms

	game = new Game();
	game->Init("CastleBuilder", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
	//Game Loop
	while (game->isRunning)
	{

		frameStart = SDL_GetTicks();

		Input::GetInstance()->Listen(game);
		game->Update();
		game->Render();
		
		frameTime = SDL_GetTicks() - frameStart;

		//Cap frames to *FPS*
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	game->Clean();

	return 0;
}