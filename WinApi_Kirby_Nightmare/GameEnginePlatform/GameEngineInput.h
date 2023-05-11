#pragma once
#include <Windows.h>
#include <map>
#include <string>

// ���� :
class GameEngineInput
{
private:
	class GameEngineKey
	{
		// Ű�� �������� �ѹ�
		bool Down = false;
		// ���������� �������ִ��� �� üũ
		bool Press = false;
		// Ű�� �������� �ѹ�
		bool Up = false;
		// Ű�� ���������� �ƹ��͵� ���������� ������
		bool Free = true;

		// �ǹ̰� ���ٰ� ����.
		float PressTime = 0.0f;

		int Key = -1;

		// Ű�� ���ȴ����� üũ�Ѵ�. true�� ����.
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

