#include "GameSystem.h"
#include "Sprite.h"

#include "Scene.h"


Scene::Scene()
{

}

Scene::~Scene()
{
	DLinkedListIterator<Sprite*> itr = _backgroundSpriteList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
		delete itr.item();
		_backgroundSpriteList.Remove(itr);
	}
}

void Scene::Init()
{
	Sprite* backgroundSprite = new Sprite("backgroundspr", true);
	backgroundSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2, GameSystem::GetInstance()->GetWindowHeight() / 2);
	_backgroundSpriteList.Append(backgroundSprite);
}

void Scene::Update(int deltaTime)
{
	DLinkedListIterator<Sprite*> backgroundItr = _backgroundSpriteList.GetIterator();
	for (backgroundItr.begin(); backgroundItr.valid(); backgroundItr.forth())
	{
		backgroundItr.item()->Update(deltaTime);
	}
}

void Scene::Render()
{
	DLinkedListIterator<Sprite*> backgroundItr = _backgroundSpriteList.GetIterator();
	for (backgroundItr.begin(); backgroundItr.valid(); backgroundItr.forth())
	{
		backgroundItr.item()->Render();
	}
}

void Scene::Deinit()
{
	DLinkedListIterator<Sprite*> backgroundItr = _backgroundSpriteList.GetIterator();
	for (backgroundItr.begin(); backgroundItr.valid(); backgroundItr.forth())
	{
		delete backgroundItr.item();
		_backgroundSpriteList.Remove(backgroundItr);
	}
}

void Scene::KeyDown(int keyCode)
{
}

void Scene::KeyUp(int keyCode)
{
}
