#include "Player.h"


Player::~Player()
{
}

void Player::Init()
{
	x = WINDOW_WIDTH / 2,
		y = WINDOW_HEIGHT / 2,
		width = 5,
		height = 5,
		turnDirection = 0,
		walkDirection = 0,
		rotationAngle = PI / 2,
		walkSpeed = 100,
		turnSpeed = 45 * (PI / 180),
		lookUpDown = 0,
		playerLookAngle = 45 * (PI / 180),
		lookUpDown = 0;
}

void Player::movePlayer(float deltaTime, Map& map)
{
	rotationAngle += turnDirection * turnSpeed * deltaTime;
	float moveStep = walkDirection * walkSpeed * deltaTime;

	float newPlayerX =  x + cos(rotationAngle) * moveStep;
	float newPlayerY =  y + sin(rotationAngle) * moveStep;

	//wall collision
	if (!map.mapHasWallAt(newPlayerX, newPlayerY)) {
		x = newPlayerX;
		y = newPlayerY;
	}
}

void Player::renderPlayer(Graphics& graphic)
{
	graphic.drawRect(
		x * MINIMAP_SCALE_FACTOR,
		y * MINIMAP_SCALE_FACTOR,
		width * MINIMAP_SCALE_FACTOR,
		height * MINIMAP_SCALE_FACTOR,
		0x0000ffff
	);
}
