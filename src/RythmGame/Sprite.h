#pragma once

//#include "SDL_Image.h"
#include "Array.h"

class Texture;

class Sprite
{
private:
	int _frameMaxCount;
	int _frame;

	int _x;
	int _y;

	bool _isLoop;
	bool _isPlay;

	int _frameInterval;
	int _frameDuration;

public:
	Sprite(const char* scriptFilename, bool isLoop);
	~Sprite();

	void Update(int deltaTime);
	void Render();

	void Play();
	void SetPosition(int x, int y);

	// Texture List
private:
	Array<Texture*>* _textureList;

public:
	void UpdateTexturePosition(Texture* texture);
};