#include <stdio.h>
#include <string.h>

#include "DLinkedList.h"
#include "GameSystem.h"

#include "Texture.h"
#include "Sprite.h"


Sprite::Sprite(const char* scriptFilename, bool isLoop)
{
	_x = GameSystem::GetInstance()->GetWindowWidth() / 2;
	_y = -GameSystem::GetInstance()->GetWindowHeight() / 2;
	
	DLinkedList<Texture*> textureList;

	char filePath[256];
	sprintf(filePath, "../Resources/scripts/%s.csv", scriptFilename);
	FILE* fp = fopen(filePath, "r");
	if (NULL == fp)
	{
		printf("File Open Error %s\n", filePath);
	}

	// 필요한 데이터
	char* textureFilename;
	float scaleWidth;
	float scaleHeight;

	char buffer[1024];
	char* record = fgets(buffer, sizeof(buffer), fp);
	while (true)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;

		char* token = strtok(record, ",");
		textureFilename = token;

		token = strtok(NULL, ",");
		scaleWidth = atof(token);

		token = strtok(NULL, ",");
		scaleHeight = atof(token);

		Texture* texture = new Texture(textureFilename);
		texture->SetScale(scaleWidth, scaleHeight);
		textureList.Append(texture);
	}

	fclose(fp);

	_frameMaxCount = textureList.GetCount();
	_textureList = new Array<Texture*>(_frameMaxCount);
	
	int frame = 0;
	DLinkedListIterator<Texture*> itr = textureList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
		Texture* texture = itr.item();
		_textureList->Set(frame, texture);
		frame++;
	}

	_isLoop = isLoop;
	if (_isLoop)
	{
		_isPlay = true;
	}
	else
	{
		_isPlay = false;
	}

	_frame = 0;
	_frameInterval = 1000 / _frameMaxCount;
	_frameDuration = 0;
}

Sprite::~Sprite()
{
	delete _textureList;
	_textureList = NULL;
}

void Sprite::Update(int deltaTime)
{
	if (false == _isPlay)
		return;

	_frameDuration += deltaTime;
	if (_frameInterval <= _frameDuration)
	{
		_frameDuration = 0;
		_frame = (_frame + 1) % _frameMaxCount;

		if (false == _isLoop)
		{
			if (0 == _frame)
			{
				_isPlay = false;
			}
		}
	}
	UpdateTexturePosition(_textureList->Get(_frame));
}

void Sprite::Render()
{
	if (false == _isPlay)
		return;

	_textureList->Get(_frame)->Render();
}

void Sprite::Play()
{
	_frame = 0;
	_isPlay = true;
}

void Sprite::SetPosition(int x, int y)
{
	_x = x;
	_y = y;
}

void Sprite::UpdateTexturePosition(Texture* texture)
{
	int x = _x- texture->GetRenderWidth() / 2;
	int y = _y- texture->GetRenderHeight() / 2;
	texture->SetPosition(x, y);
}