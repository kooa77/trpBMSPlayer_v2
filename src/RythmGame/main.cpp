#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_Image.h"
#include "SDL_ttf.h"

#include "GameSystem.h"

//#include "TitleScene.h"
//#include "GameScene.h"
#include "SceneManager.h"


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);

	if (TTF_Init() < 0)
	{
		printf("Error Init SDL Font\n");
	}
	atexit(TTF_Quit);

	// 윈도우 생성
	SDL_Window* sdlWindow = SDL_CreateWindow("RythmGame",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		GameSystem::GetInstance()->GetWindowWidth(), GameSystem::GetInstance()->GetWindowHeight(), SDL_WINDOW_OPENGL);
	SDL_Renderer* sdlRenderer = SDL_CreateRenderer(sdlWindow, 0, 0);

	GameSystem::GetInstance()->SetRenderer(sdlRenderer);

	SDL_SetRenderDrawColor(sdlRenderer, 50, 50, 50, 255);

	//SceneManager::GetInstance()->ChangeScene(eScene::SCENE_TITLE);
	SceneManager::GetInstance()->ChangeScene(eScene::SCENE_LOGO);
	
	int frame = 0;
	int prefFrame = frame;
	int currentTick = SDL_GetTicks();
	int prevTick = currentTick;
	SDL_Event sdlEvent;
	while (1)
	{
		currentTick = SDL_GetTicks();		// 현재 시간을 구한다

		// 현재 프레임을 구한다.
		frame = (currentTick % 1000) * 60;		// 60fps
		frame /= 1000;
		if (prefFrame != frame)		// frame이 진행 되었으면
		{
			prefFrame = frame;

			// frame 간 흐른 시간을 구한다.
			int deltaTime = currentTick - prevTick;
			prevTick = currentTick;

			if (SDL_PollEvent(&sdlEvent))
			{
				if (SDL_QUIT == sdlEvent.type)
					break;

				if (SDL_KEYDOWN == sdlEvent.type)
				{
					//scene->KeyDown(sdlEvent.key.keysym.sym);
					SceneManager::GetInstance()->KeyDown(sdlEvent.key.keysym.sym);
				}

				if (SDL_KEYUP == sdlEvent.type)
				{
					if (SDLK_ESCAPE == sdlEvent.key.keysym.sym)
					{
						SDL_Event newEvent;
						newEvent.type = SDL_QUIT;
						SDL_PushEvent(&newEvent);
					}
					else
					{
						//scene->KeyUp(sdlEvent.key.keysym.sym);
						SceneManager::GetInstance()->KeyUp(sdlEvent.key.keysym.sym);
					}
				}
			}

			//scene->Update(deltaTime);
			SceneManager::GetInstance()->Update(deltaTime);

			SDL_RenderClear(sdlRenderer);
			{
				//scene->Render();
				SceneManager::GetInstance()->Render();
			}
			SDL_RenderPresent(sdlRenderer);
		}
	}

	SceneManager::GetInstance()->Deinit();
	/*
	scene->Deinit();
	delete scene;
	*/

	return 0;
}
