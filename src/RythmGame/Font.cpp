//#include "SDL_ttf.h"

#include "GameSystem.h"
#include "Font.h"


Font::Font(const char* fontName, int fontSize)
{
	// 폰트 텍스쳐를 생성한다.

	/* check 44
	TTF_Font* font = TTF_OpenFont("../Resources/Font/arialbd.ttf", 24);
	SDL_Color fontColor = { 0,0,0 };
	*/
	_font = TTF_OpenFont("../Resources/Font/arialbd.ttf", 30);
	_fontColor = { 255,255,255 };

	/* check 44 - 텍스트에 의해 텍스쳐 모양이 바뀌는 부분
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Hello World", fontColor);
	_texture = SDL_CreateTextureFromSurface(GameSystem::GetInstance()->GetRenderer(), textSurface);

	SDL_QueryTexture(_texture, NULL, NULL, &_srcRect.w, &_srcRect.h);

	_srcRect.x = 0;
	_srcRect.y = 0;

	_destRect.x = 100;
	_destRect.y = 500;
	_destRect.w = _srcRect.w;
	_destRect.h = _srcRect.h;
	*/
	_destRect.x = 200;
	_destRect.y = 200;

	SetText("Score 0000");
}

Font::~Font()
{

}

void Font::SetText(const char* text)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(_font, text, _fontColor);
	_texture = SDL_CreateTextureFromSurface(GameSystem::GetInstance()->GetRenderer(), textSurface);

	SDL_QueryTexture(_texture, NULL, NULL, &_srcRect.w, &_srcRect.h);

	_srcRect.x = 0;
	_srcRect.y = 0;

	_destRect.w = _srcRect.w;
	_destRect.h = _srcRect.h;
}