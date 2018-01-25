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
	// ���� Ű ���� �ش��ϴ� �ؽ��İ� �ִ��� �˻�
	std::map<std::string, SDL_Texture*>::iterator it = _textureMap.find(filePath);	// �ݺ��� ���
	if (it != _textureMap.end())
	{
		return it->second;
	}

	// ������ ����
	SDL_Texture* texture = IMG_LoadTexture(GameSystem::GetInstance()->GetRenderer(), filePath.c_str());
	_textureMap[filePath] = texture;
	return texture;
}