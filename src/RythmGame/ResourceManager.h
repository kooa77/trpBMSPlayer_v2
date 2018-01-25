#pragma once

#include <map>
#include <string>
#include "SDL.h"

class Texture;

class ResourceManager
{
private:
	ResourceManager();
	~ResourceManager();

private:
	static ResourceManager* _instance;

public:
	static ResourceManager* GetInstance();

	// Texture
private:
	std::map<std::string, SDL_Texture*> _textureMap;

public:
	SDL_Texture* FindTexture(std::string filePath);
};

