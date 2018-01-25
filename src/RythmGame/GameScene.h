#pragma once

#include "DLinkedList.h"
#include "Array.h"
#include "Scene.h"

class Sprite;
class Track;
class Font;

class GameScene : public Scene
{
private:
	//Track* _track;
	Array<Track*>* _trackArray;
	int _gameDuration;

	Font* _text;

	int _prevScore;

public:
	GameScene();
	~GameScene();

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
