#pragma once

#include "SDL.h"

class GameSystem
{
private:
	GameSystem();
	~GameSystem();

private:
	static GameSystem* _instance;

public:
	static GameSystem* GetInstance();

public:
	int GetWindowWidth();
	int GetWindowHeight();

	// Game
private:
	int _totalPlayingTime;
	int _trackHeight;

public:
	int GetTotalPlayingTime();
	void SetTotalPlayingTime(int playintTime);

	int GetTrackHeight();
	void SetTrackHeight(int trackHeight);

	void Quit();

	// GamePlay
private:
	int _finalScore;

public:
	void SetFinalScore(int score);
	int GetFinalScore();

	// SDL
private:
	SDL_Renderer* _sdlRenderer;

public:
	SDL_Renderer* GetRenderer();
	void SetRenderer(SDL_Renderer* sdlRenderer);
};
