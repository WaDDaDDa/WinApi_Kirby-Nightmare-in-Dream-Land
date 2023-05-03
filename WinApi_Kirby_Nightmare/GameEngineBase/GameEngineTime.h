#pragma once
#include <Windows.h>

// ���� :
class GameEngineTime
{
public:
	static GameEngineTime MainTimer;

	// constrcuter destructer
	GameEngineTime();
	~GameEngineTime();

	// delete Function
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;

	float GetDeltaTime()
	{
		return FloatDelta;
	}

	void Reset();

	void Update();

protected:

private:
	// 1�ʿ� ���
	LARGE_INTEGER Count = { 0 };
	// ���� ����̳�
	LARGE_INTEGER Cur = { 0 };
	// ������ ����̾���
	LARGE_INTEGER Prev = { 0 };
	// 1ƽ�� �󸶳� �ð��� �귶����.
	__int64 Tick; // 8����Ʈ ����� �Ұ��̱⿡ 8����Ʈ ������ ����.
	double DoubleDelta;
	float FloatDelta;
};

