#pragma once

#include "DLinkedList.h"
#include "Scene.h"

class Sprite;

class TitleScene : public Scene
{
private:

public:
	TitleScene();
	~TitleScene();

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
