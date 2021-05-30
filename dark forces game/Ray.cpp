#include "Ray.h"

SDL_Texture* Ray::gTexture;



Ray::~Ray()
{
}

void Ray::normalizeAngle(float* angle)
{
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0) {
		*angle = TWO_PI + *angle;
	}
}

float Ray::distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void Ray::castRay(float rayAngle, int stripid, Player& player, Map& map)
{
}

void Ray::castRay(float rayangle, Player& player, Map& map)
{
	normalizeAngle(&rayangle);

	int isRayFacingDown = rayangle > 0 && rayangle < PI;
	int isRayFacingUp = !isRayFacingDown;

	int isRayFacingRight = rayangle < 0.5 * PI || rayangle > 1.5 * PI;
	int isRayFacingLeft = !isRayFacingRight;

	float xintercept, yintercept;
	float xstep, ystep;

	///////////////////////////////////////////
	// HORIZONTAL RAY-GRID INTERSECTION CODE
	///////////////////////////////////////////
	bool foundHorzWallHit = false;
	float horzWallHitX = 0;
	float horzWallHitY = 0;
	int horzWallContent = 0;

	// Find the y-coordinate of the closest horizontal grid intersection
	yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += isRayFacingDown ? TILE_SIZE : 0;

	// Find the x-coordinate of the closest horizontal grid intersection
	xintercept = player.x + (yintercept - player.y) / tan(rayangle);

	// Calculate the increment xstep and ystep
	ystep = TILE_SIZE;
	ystep *= isRayFacingUp ? -1 : 1;

	xstep = TILE_SIZE / tan(rayangle);
	xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
	xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	// Increment xstep and ystep until we find a wall
	while (map.isInsideMap(nextHorzTouchX, nextHorzTouchY))
	{
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

		if (map.mapHasWallAt(xToCheck, yToCheck)) {
			// found a wall hit
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallContent = map.getMapAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));
			foundHorzWallHit = true;
			break;
		}
		else {
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}

	///////////////////////////////////////////
	// VERTICAL RAY-GRID INTERSECTION CODE
	///////////////////////////////////////////
	bool foundVertWallHit = false;
	float vertWallHitX = 0;
	float vertWallHitY = 0;
	int vertWallContent = 0;

	// Find the x-coordinate of the closest horizontal grid intersection
	xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += isRayFacingRight ? TILE_SIZE : 0;

	// Find the y-coordinate of the closest horizontal grid intersection
	yintercept = player.y + (xintercept - player.x) * tan(rayangle);

	// Calculate the increment xstep and ystep
	xstep = TILE_SIZE;
	xstep *= isRayFacingLeft ? -1 : 1;

	ystep = TILE_SIZE * tan(rayangle);
	ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
	ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;

	// Increment xstep and ystep until we find a wall
	while (map.isInsideMap(nextVertTouchX, nextVertTouchY)) {
		float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (map.mapHasWallAt(xToCheck, yToCheck)) {
			// found a wall hit
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallContent = map.getMapAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));
			foundVertWallHit = true;
			break;
		}
		else {
			nextVertTouchX += xstep;
			nextVertTouchY += ystep;
		}
	}

	// Calculate both horizontal and vertical hit distances and choose the smallest one
	float horzHitDistance = foundHorzWallHit
		? distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY)
		: FLT_MAX;
	float vertHitDistance = foundVertWallHit
		? distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY)
		: FLT_MAX;

	if (vertHitDistance < horzHitDistance) {
		distance = vertHitDistance;
		wallHitX = vertWallHitX;
		wallHitY = vertWallHitY;
		wallHitContent = vertWallContent;
		wasHitVertical = true;
		rayAngle = rayangle;
	}
	else {
		distance = horzHitDistance;
		wallHitX = horzWallHitX;
		wallHitY = horzWallHitY;
		wallHitContent = horzWallContent;
		wasHitVertical = false;
		rayAngle = rayangle;
	}
}

void Ray::castAllRays(Player& player, Map& map, int& col)
{
	
		float rayAngle = player.rotationAngle + atan((col - NUM_RAYS / 2) / Dist_PROJ_PLANE);
		castRay(rayAngle,player,map);


	
}

void Ray::renderRays(Player& player, Graphics& graphic)
{
	graphic.drawLine(
		player.x * MINIMAP_SCALE_FACTOR,
		player.y * MINIMAP_SCALE_FACTOR,
		wallHitX * MINIMAP_SCALE_FACTOR,
		wallHitY * MINIMAP_SCALE_FACTOR,
		0xFF00FF00
	);
}

void Ray::renderWallProjection(Graphics& graphic, Player& player, int col, texturetest & text)
{
	float prepDistance = distance * cos(rayAngle - player.rotationAngle);

		float projectedWallHeight = (TILE_SIZE / prepDistance * Dist_PROJ_PLANE);

		int wallStripHeight = (int)projectedWallHeight;
		int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);

		int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);

		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;
		wallBottomPixel = wallBottomPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;

		//for (int y = 0; y < wallTopPixel; y++) {
		//	drawPixel(x, y, 0xff444444);
		//}

		int textureOffSetX;
		if (wasHitVertical) {
			textureOffSetX = (int)wallHitY % TILE_SIZE;

		}
		else {

			textureOffSetX = (int)wallHitX % TILE_SIZE;
		}

		//get correct texture id for map content
		int texNum = wallHitContent - 1;

		int texture_dim = 64;
		int x = col;
		//render wall from top pixel to bottom pixel
		for (int y = wallTopPixel; y < wallBottomPixel; y++) {

			int distanceFromTop = y + (wallStripHeight / 2) - (WINDOW_HEIGHT / 2);
			int textureOffSetY = distanceFromTop * ((float)texture_dim / wallStripHeight);

			text.render(col * textureOffSetY,y);
			//color_t texelColor = wallTextures[texNum].texture_buffer[(texture_width * textureOffSetY) + textureOffSetX];
			//drawPixel(x, y, texelColor);

			//if (rays[x].wasHitVertical)
			//{
			//	changeColorIntensity(&texelColor, 0.7);
			//}

			//drawPixel(x, y, texelColor);
			
			
			

		}
		//for (int y = 0; y > wallBottomPixel; y++) {
			//drawPixel(x, y, 0xff777777);
		//}
		
	
}

void Ray::wallTest(Graphics& graphic, Player& player, int& col)
{
	float perpDistance = distance * cos(rayAngle - player.rotationAngle);
	float distanceProjPlane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
	float projectedWallHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;

	int wallStripHeight = (int)projectedWallHeight;

	int wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
	wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

	int wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
	wallBottomPixel = wallBottomPixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomPixel;

	// render the wall from wallTopPixel to wallBottomPixel
	for (int y = wallTopPixel; y < wallBottomPixel; y++) {
		color_t color = 0xFF20FF00;
		
		if (wasHitVertical)
		{
			graphic.changeColorIntensity(&color, 0.7f);
		}
		graphic.drawPixel(col, y, color);
		
	} 
}




