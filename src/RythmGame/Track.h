#pragma once

#include "DLinkedList.h"

class Sprite;
class Note;

class Track
{
private:
	DLinkedList<Sprite*> _backgroundSpriteList;
	DLinkedList<Note*> _noteList;

	Sprite* _explosionSprite;
	Sprite* _failEffectSprite;

	int _judgeStartTick;
	int _judgeEndTick;

public:
	Track();
	~Track();

	void Init(int x);
	void Update(int deltaTime);
	void Render();
	void Deinit();

	// Input
private:
	bool _isKeyDown;

public:
	void KeyDown();
	void KeyUp();

	// GamePlay
private:
	int _score;

public:
	int GetScore();
};
