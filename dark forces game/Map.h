#ifndef MAP_H
#define MAP_H

#include "Defs.h"
#include "Graphics.h"



class Map
{
public:
	Map() = default;
	bool mapHasWallAt(float x, float y);
	bool isInsideMap(float x, float y);

	void renderMap(Graphics& graphic);
	int getMapAt(int i, int j);

};


#endif // !MAP_H
