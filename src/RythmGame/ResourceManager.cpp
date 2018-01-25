#include "GameSystem.h"
#include "Texture.h"
#include "ResourceManager.h"


ResourceManager* ResourceManager::_instance = 0;


ResourceManager* ResourceManager::GetInstance()
{
	if (0 == _instance)
	{
		_instance = new ResourceManager();
	}
	return _instance;
}


ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

SDL_Texture* ResourceManager::FindTexture(std::string filePath)
{
	// 현재 키 값에 해당하는 텍스쳐가 있는지 검색
	std::map<std::string, SDL_Texture*>::iterator it = _textureMap.find(filePath);	// 반복자 사용
	if (it != _textureMap.end())
	{
		return it->second;
	}

	// 없으면 생성
	SDL_Texture* texture = IMG_LoadTexture(GameSystem::GetInstance()->GetRenderer(), filePath.c_str());
	_textureMap[filePath] = texture;
	return texture;
}