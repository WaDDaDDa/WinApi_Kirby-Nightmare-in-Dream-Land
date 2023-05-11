#pragma once

// GameEngineObject를 상속받는 class들은 다형성을 가진다.
// virtual로 선언된 함수들을 사용할수있고 안할수도있는 제안을 받는다.
class GameEngineObject
{

	friend class GameEngineLevel;
public:
    GameEngineObject();
    ~GameEngineObject();

	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	// 시작하고.
	virtual void Start() {}

	// 행동한고.
	virtual void Update(float _Delta) {}

	// 그려지고.
	virtual void Render() {}

	// 정리된다.
	virtual void Release() {}
	// 업데이트 온
	void On()
	{
		IsUpdateValue = true;
	}
	// 업데이트 오프
	void Off()
	{
		IsUpdateValue = false;
	}
	// 데이터의 죽음
	void Death()
	{
		IsDeathValue = true;
	}
	// 데이터가 죽어있지않고 업데이트 온이면 true 출력. <== 이래야만 업데이트 가능.
	bool IsUpdate()
	{
		return true == IsUpdateValue && false == IsDeathValue; // Death인상태이면 업데이트 하면안됨.
	}
	// 죽었는지를 확인.
	virtual bool IsDeath()
	{
		return IsDeathValue;
	}

	void SetOrder(int _Order)
	{
		Order = _Order;
	}

	float GetLiveTime()
	{
		return LiveTime;
	}

	void ResetLiveTime()
	{
		LiveTime = 0.0f;
	}

protected:


private:
	int Order = 0;
	bool IsUpdateValue = true; // 이걸 false로 만들면 됩니다.
	bool IsDeathValue = false; // 아예 메모리에서 날려버리고 싶어.

	float LiveTime = 0.0f;

	void AddLiveTime(float _DeltaTime)
	{
		LiveTime += _DeltaTime;
	}
	
};

