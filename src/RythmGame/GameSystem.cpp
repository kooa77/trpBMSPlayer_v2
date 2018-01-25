#include "GameSystem.h"


GameSystem* GameSystem::_instance = 0;


GameSystem* GameSystem::GetInstance()
{
	if (0 == _instance)
	{
		_instance = new GameSystem();
	}
	return _instance;
}


GameSystem::GameSystem()
{
}

GameSystem::~GameSystem()
{
}

int GameSystem::GetWindowWidth()
{
	return 1024;
}

int GameSystem::GetWindowHeight()
{
	return 800;
}

int GameSystem::GetTotalPlayingTime()
{
	return _totalPlayingTime;
}

void GameSystem::SetTotalPlayingTime(int playintTime)
{
	_totalPlayingTime = playintTime;
}

int GameSystem::GetTrackHeight()
{
	return _trackHeight;
}

void GameSystem::SetTrackHeight(int trackHeight)
{
	_trackHeight = trackHeight;
}

void GameSystem::Quit()
{
	SDL_Event quitEvent;
	quitEvent.type = SDL_QUIT;
	SDL_PushEvent(&quitEvent);
}

void GameSystem::SetFinalScore(int score)
{
	_finalScore = score;
}

int GameSystem::GetFinalScore()
{
	return _finalScore;
}

SDL_Renderer* GameSystem::GetRenderer()
{
	return _sdlRenderer;
}

void GameSystem::SetRenderer(SDL_Renderer* sdlRenderer)
{
	_sdlRenderer = sdlRenderer;
}