#pragma once

class Sprite;

class Note
{
private:
	Sprite* _sprite;

	int _updateDuration;
	int _x;
	int _y;

	float _startSec;
	int _judgeLineOffset;

	bool _isLive;
	bool _isPassed;

public:
	Note(float sec, int judgeLineOffset);
	~Note();

	void Init(int x);

	void Udate(int deltaTime);
	void Render();

	void UpdatePosition(int deltaTime);

	void SetLive(bool isLive);
	bool IsLive();

	void Passed();
	bool IsPassed();
	
	int GetCurrentTime();
};
