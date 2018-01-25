#include "GameSystem.h"
#include "Sprite.h"

#include "Note.h"


Note::Note(float sec, int judgeLineOffset)
{
	_sprite = new Sprite("notespr", true);

	_judgeLineOffset = judgeLineOffset;
	_x = GameSystem::GetInstance()->GetWindowWidth() / 2;

	_startSec = sec;

	_isLive = true;
	_isPassed = false;
}

Note::~Note()
{
	delete _sprite;
}

void Note::Init(int x)
{
	_x = x;
	int startTick = GameSystem::GetInstance()->GetTotalPlayingTime() - (_startSec * 1000.0f);
	_updateDuration = startTick;
	UpdatePosition(0);
}

void Note::Udate(int deltaTime)
{
	if (false == _isLive)
		return;

	UpdatePosition(deltaTime);
	_sprite->Update(deltaTime);
}

void Note::Render()
{
	if (false == _isLive)
		return;

	_sprite->Render(); 
}

void Note::UpdatePosition(int deltaTime)
{
	_updateDuration += deltaTime;

	float timePositionRate = (float)_updateDuration / (float)GameSystem::GetInstance()->GetTotalPlayingTime();
	float positionByTick = (float)GameSystem::GetInstance()->GetTrackHeight() * timePositionRate;
	_y = positionByTick - (GameSystem::GetInstance()->GetTrackHeight() - GameSystem::GetInstance()->GetWindowHeight()) - _judgeLineOffset;

	_sprite->SetPosition(_x, _y);

	if (GameSystem::GetInstance()->GetTotalPlayingTime()+500 < _updateDuration)
	{
		_isLive = false;
	}
}

void Note::SetLive(bool isLive)
{
	_isLive = isLive;
}

bool Note::IsLive()
{
	return _isLive;
}

void Note::Passed()
{
	_isPassed = true;
}

bool Note::IsPassed()
{
	return _isPassed;
}

int Note::GetCurrentTime()
{
	return _updateDuration;
}
