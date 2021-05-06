#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"
#include "Defs.h"
#include "Graphics.h"



class Player
{
public:
	Player() = default;
	~Player();
	void Init();
	void movePlayer(float deltaTime, Map& map);
	void renderPlayer(Graphics& graphic);

public:
	float x;
	float y;
	float width;
	float height;
	int turnDirection; // -1 for left, +1 for right
	int walkDirection; // -1 for back, +1 for front
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
	int islookingupdown;
	float lookUpDown;
	float playerLookAngle;
};

#endif // !PLAYER_H
