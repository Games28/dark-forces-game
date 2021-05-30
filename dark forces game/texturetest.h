#ifndef TEXTURETEST_H
#define TEXTUERTEST_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include "Defs.h"
#include "Graphics.h"

class texturetest
{
public:
	texturetest() = default;
	~texturetest();
	void init();
	bool LoadFromFile(std::string path);
	bool loadFromRenderedText(std::string texturetext, SDL_Color textcolor);
	void free();
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendeMoe(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void loadTexture();

	//Gets image dimensions
	int getWidth();
	int getHeight();

	//Pixel manipulators
	bool lockTexture();
	bool unlockTexture();
	void* getPixels();
	int getPitch();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	void* mPixels;
	int mPitch;

	//Image dimensions
	int mWidth;
	int mHeight;
};

#endif