#pragma once
#include <Windows.h>
#include <map>

// 설명 :
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

	template<typename EnumType>
	float GetTimeScale(EnumType _Order)
	{
		return GetTimeScale(static_cast<int>(_Order));
	}

	float GetTimeScale(int _Order)
	{
		if (TimeScale.end() == TimeScale.find(_Order))
		{
			TimeScale[_Order] = 1.0f;
		}

		return TimeScale[_Order];
	}

	template<typename EnumType>
	void SetTimeScale(EnumType _Order, float _TimeScale)
	{
		SetTimeScale(static_cast<int>(_Order), _TimeScale);
	}

	void SetTimeScale(int _Order, float _TimeScale)
	{
		TimeScale[_Order] = _TimeScale;
	}

	void SetAllTimeScale(float _TimeScale)
	{
		for (std::pair<const int, float>& Order : TimeScale)
		{
			Order.second = _TimeScale;
		}
	}

protected:

private:
	// 1초에 몇번
	LARGE_INTEGER Count = { 0 };
	// 현재 몇번이냐
	LARGE_INTEGER Cur = { 0 };
	// 이전에 몇번이었냐
	LARGE_INTEGER Prev = { 0 };
	// 1틱에 얼마나 시간이 흘렀는지.
	__int64 Tick; // 8바이트 계산을 할것이기에 8바이트 정수로 선언.
	double DoubleDelta;
	float FloatDelta;

	// int 오브젝트의 업데이트 오더
	std::map<int, float> TimeScale;
};

