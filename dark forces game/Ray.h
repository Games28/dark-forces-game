#ifndef RAY_H
#define RAY_H

#include <SDL.h>
#include <SDL_image.h>
#include "Defs.h"
#include "Player.h"
#include "Map.h"
#include "Graphics.h"
#include <float.h>
#include "texturetest.h"



class Ray
{
public:
	Ray() = default;
	static SDL_Texture* gTexture;
	
	~Ray();
	void normalizeAngle(float* angle);
	float distanceBetweenPoints(float x1, float y1, float x2, float y2);
	void castRay(float rayAngle, int stripid, Player& player, Map& map);
	void castRay(float rayangle, Player& player, Map& map);
	void castAllRays(Player& player, Map& map, int& col);
	void renderRays(Player& player, Graphics& graphic);
	void renderWallProjection(Graphics& graphic, Player& player, int col, texturetest& text);
	void wallTest(Graphics& graphic, Player& player, int& col);
	//void loadTexture();
	

public:
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;
	bool wasHitVertical;

	int wallHitContent;
	void* Pixels;
	//texturetest  theTexture;
};

#endif // !RAY_H
