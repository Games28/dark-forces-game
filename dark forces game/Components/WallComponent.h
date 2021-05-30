#ifndef WALLCOMPONENT_H
#define WALLCOMPONENT_H

#include "TransformComponent.h"
//#include "../Graphics.h"
//#include "../TextureManager.h"
#include "../AssetManager.h"
#include <SDL.h>

class WallComponent : public Component
{
public:
	WallComponent(const char* filePath)
	{
		SetTexture(filePath);
	}

	void SetTexture(std::string assetTextureId)
	{
		texture = Game::assetManager->GetTexture(assetTextureId);

	}

	void Initialize() override
	{
		transform = owner->GetComponent<TransformComponent>();
		sourceRectangle.x = 0;
		sourceRectangle.y = 0;
		sourceRectangle.w = transform->width;
		sourceRectangle.h = transform->height;
	}

	void Update(float deltaTime) override
	{
		/*if (isAnimated)
		{
			sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);

		}
		sourceRectangle.y = animationIndex * transform->height;*/

		destinationRectangle.x = static_cast<int>(transform->position.x);
		destinationRectangle.y = static_cast<int>(transform->position.y);
		destinationRectangle.w = transform->width * transform->scale;
		destinationRectangle.h = transform->height * transform->scale;
	}

	void Render() override
	{
		TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
	}

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
private:
	SDL_Texture* texture;
	TransformComponent* transform;
	void* Pixels;
	int mPitch;
	int X;
	int Y;
	int width;
	int height;
	SDL_Rect sourceRectangle;
	SDL_Rect destinationRectangle;
};

#endif // !WALLCOMPONENT_H
