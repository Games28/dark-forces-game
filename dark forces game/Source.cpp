#include <SDL.h>
#include "Game.h"

int main(int argc, char* argv[])
{
	Game* game = new Game();

	game->Setup();

	while (game->isGameRunning)
	{
		game->processInput();
		game->Update();
		game->Render();
	}

	game->ReleaseResources();

	return 0;
}