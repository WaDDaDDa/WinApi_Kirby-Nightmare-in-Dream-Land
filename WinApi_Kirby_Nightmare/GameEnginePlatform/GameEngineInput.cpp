#include "GameEngineInput.h"

GameEngineInput::GameEngineInput()
{
}

GameEngineInput::~GameEngineInput()
{
}


void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
	if (true == KeyCheck())
	{
		// 키가 눌렸다.

		PressTime += _DeltaTime;

		// 여태까지 키가 눌렸던적이 없다는 거죠.
		if (true == Free)
		{
			Down = true;
			Press = true;
			Up = false;
			Free = false;
		}
		else if (true == Down)
		{
			Down = false;
			Press = true;
			Up = false;
			Free = false;
		}

	}
	else
	{
		PressTime = 0.0f;
		// 키가 눌리지 않았다.
		if (true == Press)
		{
			Down = false;
			Press = false;
			Up = true;
			Free = true;
		}
		else if (true == Up)
		{
			Down = false;
			Press = false;
			Up = false;
			Free = true;
		}
	}
}