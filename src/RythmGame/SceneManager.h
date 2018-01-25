#pragma once


enum eScene
{
	SCENE_LOGO,
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT,
};

class Scene;

class SceneManager
{
private:
	SceneManager();
	~SceneManager();

private:
	static SceneManager* _instance;

public:
	static SceneManager* GetInstance();

public:
	void Update(int deltaTime);
	void Render();
	void Deinit();

	void KeyDown(unsigned int keyCode);
	void KeyUp(unsigned int keyCode);

	// Scene
private:
	Scene* _scene;

public:
	void ChangeScene(eScene scene);
};
