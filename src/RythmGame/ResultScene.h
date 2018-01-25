#pragma once


#include "Scene.h"

class Sprite;
class Font;

class ResultScene : public Scene
{
private:
	Font* _text;

public:
	ResultScene();
	~ResultScene();

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
