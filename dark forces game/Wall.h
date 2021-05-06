#ifndef WALL_H
#define WALL_H

#include "Defs.h"
#include "Graphics.h"
#include "Ray.h"


class Wall
{
public:
	Wall() = default;
	~Wall();
	void changeColorIntensity(color_t* color, float factor);
	void renderWallProjection(Graphics& graphic);
	void wallTest(Graphics& graphic);

};

#endif // !WALL_H
