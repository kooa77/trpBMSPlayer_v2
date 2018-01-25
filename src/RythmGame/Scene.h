#pragma once

#include "DLinkedList.h"

class Sprite;

class Scene
{
protected:
	DLinkedList<Sprite*> _backgroundSpriteList;

public:
	Scene();
	virtual ~Scene();

public:
	virtual void Init();
	virtual void Update(int deltaTime);
	virtual void Render();
	virtual void Deinit();

	// Input
public:
	virtual void KeyDown(int keyCode);
	virtual void KeyUp(int keyCode);
};
