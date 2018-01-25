#include <stdio.h>

#include "LogoScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ResultScene.h"

#include "SceneManager.h"


SceneManager* SceneManager::_instance = 0;


SceneManager* SceneManager::GetInstance()
{
	if (0 == _instance)
	{
		_instance = new SceneManager();
	}
	return _instance;
}


SceneManager::SceneManager()
{
	_scene = NULL;
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update(int deltaTime)
{
	_scene->Update(deltaTime);
}

void SceneManager::Render()
{
	_scene->Render();
}

void SceneManager::Deinit()
{
	if (NULL != _scene)
	{
		_scene->Deinit();
		delete _scene;
		_scene = NULL;
	}
}

void SceneManager::KeyDown(unsigned int keyCode)
{
	_scene->KeyDown(keyCode);
}

void SceneManager::KeyUp(unsigned int keyCode)
{
	_scene->KeyUp(keyCode);
}

void SceneManager::ChangeScene(eScene scene)
{
	if (NULL != _scene)
	{
		_scene->Deinit();
	}
	
	switch (scene)
	{
	case eScene::SCENE_LOGO:
		_scene = new LogoScene();
		break;
	case eScene::SCENE_TITLE:
		_scene = new TitleScene();
		break;
	case eScene::SCENE_GAME:
		_scene = new GameScene();
		break;
	case eScene::SCENE_RESULT:
		_scene = new ResultScene();
		break;
	}
	_scene->Init();
}
