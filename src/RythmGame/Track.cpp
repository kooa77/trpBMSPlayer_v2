#include <stdio.h>
#include <stdlib.h>

#include "GameSystem.h"

#include "Sprite.h"
#include "Note.h"
#include "Track.h"


Track::Track()
{
	_isKeyDown = false;

	_explosionSprite = NULL;
	_failEffectSprite = NULL;

	_score = 0;
}

Track::~Track()
{
	DLinkedListIterator<Sprite*> itr = _backgroundSpriteList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
		delete itr.item();
		_backgroundSpriteList.Remove(itr);
	}

	if (NULL != _explosionSprite)
	{
		delete _explosionSprite;
		_explosionSprite = NULL;
	}

	if (NULL != _failEffectSprite)
	{
		delete _failEffectSprite;
		_failEffectSprite = NULL;
	}
}

void Track::Init(int x)
{
	int judgeLineOffset = 100;

	Sprite* backgroundSprite = new Sprite("trackspr", true);
	backgroundSprite->SetPosition(x, GameSystem::GetInstance()->GetWindowHeight() / 2);
	_backgroundSpriteList.Append(backgroundSprite);

	Sprite* judgeLineSprite = new Sprite("judgelinespr", true);
	judgeLineSprite->SetPosition(x, GameSystem::GetInstance()->GetWindowHeight() - judgeLineOffset);
	_backgroundSpriteList.Append(judgeLineSprite);
	
	// 판정선에 위치하도록 조정한다.
	_explosionSprite = new Sprite("successeffectspr", false);
	_explosionSprite->SetPosition(x, GameSystem::GetInstance()->GetWindowHeight() - judgeLineOffset);

	_failEffectSprite = new Sprite("faileffectspr", false);
	_failEffectSprite->SetPosition(x, 300);

	float totalPlayingSec = (float)GameSystem::GetInstance()->GetTotalPlayingTime() / 1000.0f;
	float noteSec = 1.0f;
	while (noteSec < totalPlayingSec)
	{
		Note* note = new Note(noteSec, judgeLineOffset);
		note->Init(x);
		_noteList.Append(note);

		int randValue = rand() % 3;
		switch (randValue)
		{
		case 0:
			noteSec += 0.25f;
			break;
		case 1:
			noteSec += 0.5f;
			break;
		case 2:
			noteSec += 0.75f;
			break;
		default:
			noteSec += 1.0f;
			break;
		}
	}

	int judgeTick = GameSystem::GetInstance()->GetTotalPlayingTime();
	_judgeStartTick = judgeTick - 100;
	_judgeEndTick = judgeTick + 100;
}

void Track::Update(int deltaTime)
{
	DLinkedListIterator<Sprite*> backgroundItr = _backgroundSpriteList.GetIterator();
	for (backgroundItr.begin(); backgroundItr.valid(); backgroundItr.forth())
	{
		backgroundItr.item()->Update(deltaTime);
	}

	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
		Note* note = itr.item();
		/*
		if (note->IsLive())
		{
			note->Udate(deltaTime);

			if (_judgeEndTick < note->GetCurrentTime() && false == note->IsPassed())
			{
				note->Passed();
				_failEffectSprite->Play();
			}
		}
		else
		{
			delete itr.item();
			_noteList.Remove(itr);
		}
		*/
		note->Udate(deltaTime);

		if (_judgeEndTick < note->GetCurrentTime() && false == note->IsPassed())
		{
			note->Passed();
			_failEffectSprite->Play();
		}
	}

	_explosionSprite->Update(deltaTime);
	_failEffectSprite->Update(deltaTime);
}

void Track::Render()
{
	DLinkedListIterator<Sprite*> backgroundItr = _backgroundSpriteList.GetIterator();
	for (backgroundItr.begin(); backgroundItr.valid(); backgroundItr.forth())
	{
		backgroundItr.item()->Render();
	}

	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
		itr.item()->Render();
	}

	_explosionSprite->Render();
	_failEffectSprite->Render();
}

void Track::Deinit()
{
	DLinkedListIterator<Sprite*> backgroundItr = _backgroundSpriteList.GetIterator();
	for (backgroundItr.begin(); backgroundItr.valid(); backgroundItr.forth())
	{
		delete backgroundItr.item();
		_backgroundSpriteList.Remove(backgroundItr);
	}

	if (NULL != _explosionSprite)
	{
		delete _explosionSprite;
		_explosionSprite = NULL;
	}

	if (NULL != _failEffectSprite)
	{
		delete _failEffectSprite;
		_failEffectSprite = NULL;
	}

	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
		delete itr.item();
		_noteList.Remove(itr);
	}
}

void Track::KeyDown()
{
	if (_isKeyDown)
		return;
	_isKeyDown = true;

	bool isJudge = false;
	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
		Note* note = itr.item();

		// check 53
		if (false == note->IsLive())
		{
			continue;
		}			

		if (note->IsPassed())
		{
			continue;
		}

		// 아직 도달하지 않았다.
		if (note->GetCurrentTime() < _judgeStartTick)
		{
			break;
		}

		// 판정
		if (_judgeStartTick <= note->GetCurrentTime() && note->GetCurrentTime() <= _judgeEndTick)
		{
			isJudge = true;
			break;
		}
	}

	if (isJudge)
	{
		_score += 10;
		_explosionSprite->Play();

		/*
		delete itr.item();
		_noteList.Remove(itr);	// 이 부분 때문에, 위치가 어긋 나는 경우가 있음. 제거 대신 하이드로
		*/
		itr.item()->SetLive(false);
	}
}

void Track::KeyUp()
{
	_isKeyDown = false;
}

int Track::GetScore()
{
	return _score;
}