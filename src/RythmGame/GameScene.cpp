#include <stdio.h>

#include "sdl_mixer.h"

#include "SceneManager.h"
#include "GameSystem.h"
#include "Font.h"
#include "Sprite.h"
#include "Track.h"

#include "GameScene.h"


GameScene::GameScene()
{
	_prevScore = 0;
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	Scene::Init();

	Sprite* backgroundDecoSprite = new Sprite("backgrounddecospr", true);
	backgroundDecoSprite->SetPosition(200, 100);
	_backgroundSpriteList.Append(backgroundDecoSprite);

	float totalPlayingSec = 60.0f;

	int totalPlayingTime = totalPlayingSec * 1000;
	GameSystem::GetInstance()->SetTotalPlayingTime(totalPlayingTime);


	// BPM 적용
	int BPM = 90;
	int tempo = BPM / 60;
	int trackHeight = GameSystem::GetInstance()->GetWindowHeight() * totalPlayingSec * tempo;
	GameSystem::GetInstance()->SetTrackHeight(trackHeight);

	int trackCount = 5;
	_trackArray = new Array<Track*>(trackCount);

	int startX = 300;
	for (int i = 0; i < trackCount; i++)
	{
		int x = startX + (i * 64) + 2;

		Track* track = new Track();
		track->Init(x);
		_trackArray->Set(i, track);
	}

	_gameDuration = 0;

	// Font
	_text = new Font("arialbd.ttf", 24);

	// 음악 플레이
	int result = Mix_Init(MIX_INIT_MP3);
	if (MIX_INIT_MP3 == result)
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
		Mix_Music* music = Mix_LoadMUS("../Resources/Music/The Concept of Love.mp3");
		if (NULL != music)
		{
			Mix_PlayMusic(music, 1);
		}
		else
		{
			printf("Error LoadMusic\n");
		}
	}
}

void GameScene::Update(int deltaTime)
{
	Scene::Update(deltaTime);

	if (_gameDuration <= GameSystem::GetInstance()->GetTotalPlayingTime() + 2000)
	{
		_gameDuration += deltaTime;

		/*
		_track->Update(deltaTime);

		if (_prevScore != _track->GetScore())
		{
			_prevScore = _track->GetScore();

			char text[256];
			sprintf(text, "Score %04d", _track->GetScore());
			_text->SetText(text);
		}
		*/
		int finalScore = 0;
		for (int i = 0; i < _trackArray->Size() ; i++)
		{
			Track* track = _trackArray->Get(i);
			track->Update(deltaTime);
			finalScore += track->GetScore();
		}

		if (_prevScore != finalScore)
		{
			_prevScore = finalScore;

			char text[256];
			sprintf(text, "Score %04d", finalScore);
			_text->SetText(text);
		}
	}
	else
	{
		Mix_PauseMusic();
		//GameSystem::GetInstance()->SetFinalScore(_track->GetScore());
		GameSystem::GetInstance()->SetFinalScore(_prevScore);
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_RESULT);
	}
}

void GameScene::Render()
{
	Scene::Render();

	//_track->Render();
	for (int i = 0; i < _trackArray->Size(); i++)
	{
		Track* track = _trackArray->Get(i);
		track->Render();
	}

	_text->Render();
}

void GameScene::Deinit()
{
	Scene::Deinit();

	/*
	_track->Deinit();
	delete _track;
	*/
	for (int i = 0; i < _trackArray->Size(); i++)
	{
		Track* track = _trackArray->Get(i);
		track->Deinit();
		delete track;
	}
	delete _trackArray;
	_trackArray = NULL;
}

void GameScene::KeyDown(int keyCode)
{
	switch (keyCode)
	{
		/*
	case SDLK_SPACE:
		_track->KeyDown();
		break;
		*/
	case SDLK_d:
		_trackArray->Get(0)->KeyDown();
		break;
	case SDLK_f:
		_trackArray->Get(1)->KeyDown();
		break;
		/*
	case SDLK_SPACE:
		_trackArray->Get(2)->KeyDown();
		break;
	case SDLK_j:
		_trackArray->Get(3)->KeyDown();
		break;
	case SDLK_k:
		_trackArray->Get(4)->KeyDown();
		break;
		*/
	}
}

void GameScene::KeyUp(int keyCode)
{
	switch (keyCode)
	{
		/*
	case SDLK_SPACE:
		_track->KeyUp();
		break;
		*/
	case SDLK_d:
		_trackArray->Get(0)->KeyUp();
		break;
	case SDLK_f:
		_trackArray->Get(1)->KeyUp();
		break;
		/*
	case SDLK_SPACE:
		_trackArray->Get(2)->KeyUp();
		break;
	case SDLK_j:
		_trackArray->Get(3)->KeyUp();
		break;
	case SDLK_k:
		_trackArray->Get(4)->KeyUp();
		break;
		*/
	}
}
