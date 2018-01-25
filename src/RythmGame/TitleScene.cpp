#include "SceneManager.h"
#include "GameSystem.h"
#include "Sprite.h"

#include "TitleScene.h"


TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	//Scene::Init();
	Sprite* backgroundSprite = new Sprite("titlebackgroundspr", true);
	backgroundSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2, GameSystem::GetInstance()->GetWindowHeight() / 2);
	_backgroundSpriteList.Append(backgroundSprite);
}

void TitleScene::Update(int deltaTime)
{
	Scene::Update(deltaTime);
}

void TitleScene::Render()
{
	Scene::Render();
}

void TitleScene::Deinit()
{
	Scene::Deinit();
}

void TitleScene::KeyDown(int keyCode)
{
	switch (keyCode)
	{
	case SDLK_SPACE:
		break;
	}
}

void TitleScene::KeyUp(int keyCode)
{
	switch (keyCode)
	{
	case SDLK_SPACE:
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_GAME);
		break;
	}
}
