#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include "TextureManager.h"
#include "EntityManager.h"

class AssetManager
{
private:
	AssetManager() = default;
	EntityManager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, SDL_Texture*> testtextures;
public:
	AssetManager(EntityManager* manager);
	~AssetManager();
	void ClearData();
	void AddTexture(std::string textureId, const char* filePath);
	void testaddTexture(std::string Id, const char* filePath);
	SDL_Texture* testGetTexture(std::string textureid);
	SDL_Texture* GetTexture(std::string textureId);
};


#endif