#include "SceneManager.h"
#include "GameSystem.h"
#include "Sprite.h"

#include "LogoScene.h"


LogoScene::LogoScene()
{
	_waitTick = 2000;
	_updateTick = 0;
}

LogoScene::~LogoScene()
{
}

void LogoScene::Init()
{
	//Scene::Init();
	Sprite* backgroundSprite = new Sprite("logobackgroundspr", true);
	backgroundSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2, GameSystem::GetInstance()->GetWindowHeight() / 2);
	_backgroundSpriteList.Append(backgroundSprite);
}

void LogoScene::Update(int deltaTime)
{
	Scene::Update(deltaTime);

	if (_waitTick < _updateTick)
	{
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_TITLE);
	}
	_updateTick += deltaTime;
}

void LogoScene::Render()
{
	Scene::Render();
}

void LogoScene::Deinit()
{
	Scene::Deinit();
}

void LogoScene::KeyDown(int keyCode)
{
	switch (keyCode)
	{
	case SDLK_SPACE:
		break;
	}
}

void LogoScene::KeyUp(int keyCode)
{
	switch (keyCode)
	{
	case SDLK_SPACE:
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_TITLE);
		break;
	}
}
