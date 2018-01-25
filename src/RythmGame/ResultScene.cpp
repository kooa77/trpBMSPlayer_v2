#include <stdio.h>

#include "SceneManager.h"
#include "GameSystem.h"
#include "Sprite.h"
#include "Font.h"

#include "ResultScene.h"


ResultScene::ResultScene()
{

}

ResultScene::~ResultScene()
{
}

void ResultScene::Init()
{
	//Scene::Init();
	Sprite* backgroundSprite = new Sprite("resultbackgroundspr", true);
	backgroundSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2, GameSystem::GetInstance()->GetWindowHeight() / 2);
	_backgroundSpriteList.Append(backgroundSprite);

	// Font
	_text = new Font("arialbd.ttf", 24);

	char text[256];
	sprintf(text, "Final Score %04d", GameSystem::GetInstance()->GetFinalScore());
	_text->SetText(text);
}

void ResultScene::Update(int deltaTime)
{
	Scene::Update(deltaTime);
}

void ResultScene::Render()
{
	Scene::Render();
	_text->Render();
}

void ResultScene::Deinit()
{
	Scene::Deinit();
}

void ResultScene::KeyDown(int keyCode)
{
	switch (keyCode)
	{
	case SDLK_SPACE:
		break;
	}
}

void ResultScene::KeyUp(int keyCode)
{
	switch (keyCode)
	{
	case SDLK_SPACE:
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_TITLE);
		break;
	}
}
