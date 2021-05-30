#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	SDL_Surface* surface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Graphics::renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
	
}

 void TextureManager::Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Graphics::renderer, texture, &sourceRectangle, &destinationRectangle,
		  0.0, NULL, flip);

}

 SDL_Texture* TextureManager::testtextureload(const char* fileName)
 {
	 SDL_Surface* surface = IMG_Load(fileName);
	 SDL_Texture* texture = SDL_CreateTextureFromSurface(Graphics::renderer, surface);
	 SDL_FreeSurface(surface);
	 return texture;
 }

