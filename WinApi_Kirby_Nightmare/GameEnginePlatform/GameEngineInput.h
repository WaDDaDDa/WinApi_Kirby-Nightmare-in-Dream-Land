#pragma once
#include <Windows.h>
#include <map>
#include <string>

// 설명 :
class GameEngineInput
{
private:
	class GameEngineKey
	{
		// 키가 눌렷을때 한번
		bool Down = false;
		// 눌렸을때와 눌리고있는중 을 체크
		bool Press = false;
		// 키가 떼졌을때 한번
		bool Up = false;
		// 키가 떼졌을때와 아무것도 눌리고있지 않을때
		bool Free = true;

		// 의미가 없다고 봐요.
		float PressTime = 0.0f;

		int Key = -1;

		// 키가 눌렸는지를 체크한다. true면 눌림.
		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key);
		}

		void Update(float _DeltaTime);
	};

public:
	// constrcuter destructer
	GameEngineInput();
	~GameEngineInput();

	// delete Function
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;

protected:

private:
	static std::map<std::string, GameEngineKey> AllKeys;
};

