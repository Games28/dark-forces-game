#include "AssetManager.h"

AssetManager::AssetManager(EntityManager* manager) : manager(manager)
{
	
}

AssetManager::~AssetManager()
{
}


void AssetManager::ClearData()
{
	textures.clear();
}

void AssetManager::AddTexture(std::string textureId, const char* filePath)
{
	textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

void AssetManager::testaddTexture(std::string Id, const char* filePath)
{
	testtextures.emplace(Id, TextureManager::testtextureload(filePath));
	
}

SDL_Texture* AssetManager::testGetTexture(std::string textureid)
{
	return testtextures[textureid];
}

SDL_Texture* AssetManager::GetTexture(std::string textureId)
{
	return textures[textureId];
}


