#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <iostream>
#include "Defs.h"




class Graphics
{
public:
	Graphics() = default;
	
	static SDL_Renderer* renderer;
	static SDL_Window* window;
	static SDL_Surface* surface;
	bool initializeWindow();
	void destroyWindow();
	void clearColorBuffer(color_t color);
	void renderColorBuffer();
	void changeColorIntensity(color_t* color, float factor);
	void drawPixel(int x, int y, color_t color);
	void drawRect(int x, int y, int width, int height, color_t color);
	void drawLine(int x0, int y0, int x1, int y1, color_t color);
	

};


#endif // !GRAPHICS_H
