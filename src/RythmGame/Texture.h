#pragma once

#include "SDL_Image.h"

class Texture
{
public:
	Texture() {}
	Texture(const char* fileName);
	~Texture();

	void SetScale(float scaleW, float scaleH);
	void SetPosition(int x, int y);
	void Render();

	int GetRenderWidth();
	int GetRenderHeight();

	// SDL
protected:
	SDL_Rect _srcRect;
	SDL_Rect _destRect;
	SDL_Texture* _texture;
};