#ifndef GAME_H
#define GAME_H


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Graphics.h"
#include "Defs.h"
#include "Map.h"
#include "Player.h"
#include "Ray.h"
#include "Components/Component.h"


class Game
{
public:
	Game() = default;
	~Game();
	void Setup();
	void processInput();
	void Update();
	void Render();
	void ReleaseResources();
	bool isGameRunning;
	int ticksLastFrame = 0;
private:
	Graphics graphic;
	Map map;
	Player player;
	Ray rays[NUM_RAYS];
};
#endif // !GAME_H
