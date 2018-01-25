#pragma once

#include "Scene.h"

class Sprite;

class LogoScene : public Scene
{
private:
	int _waitTick;
	int _updateTick;

public:
	LogoScene();
	~LogoScene();

public:
	void Init();
	void Update(int deltaTime);
	void Render();
	void Deinit();

	// Input
public:
	void KeyDown(int keyCode);
	void KeyUp(int keyCode);
};

