#include "Game.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"


Game::~Game()
{
}

void Game::Setup()
{
	player.Init();
	
	isGameRunning = graphic.initializeWindow();
}

void Game::processInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT: {
		isGameRunning = false;
		break;
	}
	case SDL_KEYDOWN: {
		if (event.key.keysym.sym == SDLK_ESCAPE)
			isGameRunning = false;
		if (event.key.keysym.sym == SDLK_UP)
			player.walkDirection = +1;
		if (event.key.keysym.sym == SDLK_DOWN)
			player.walkDirection = -1;
		if (event.key.keysym.sym == SDLK_RIGHT)
			player.turnDirection = +1;
		if (event.key.keysym.sym == SDLK_LEFT)
			player.turnDirection = -1;
		if (event.key.keysym.sym == SDLK_w)

			player.lookUpDown += 4;

		if (event.key.keysym.sym == SDLK_s)

			player.lookUpDown += -4;

		break;
	}
	case SDL_KEYUP: {
		if (event.key.keysym.sym == SDLK_UP)
			player.walkDirection = 0;
		if (event.key.keysym.sym == SDLK_DOWN)
			player.walkDirection = 0;
		if (event.key.keysym.sym == SDLK_RIGHT)
			player.turnDirection = 0;
		if (event.key.keysym.sym == SDLK_LEFT)
			player.turnDirection = 0;
		if (event.key.keysym.sym == SDLK_w)

			player.lookUpDown += player.lookUpDown * 0;
		if (event.key.keysym.sym == SDLK_s)

			player.lookUpDown += player.lookUpDown * 0;

		break;
	}
	}
}

void Game::Update()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TIME_LENGTH));


	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	ticksLastFrame = SDL_GetTicks();
	player.movePlayer(deltaTime, map);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		rays[i].castAllRays(player, map, i);
	}
}

void Game::Render()
{
	graphic.clearColorBuffer(0xFFFF0000);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		rays[i].wallTest(graphic, player, i);
	}
	map.renderMap(graphic);
	player.renderPlayer(graphic);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		rays[i].renderRays(player, graphic);
	}

	graphic.renderColorBuffer();
}

void Game::ReleaseResources()
{
	graphic.destroyWindow();
	
}
