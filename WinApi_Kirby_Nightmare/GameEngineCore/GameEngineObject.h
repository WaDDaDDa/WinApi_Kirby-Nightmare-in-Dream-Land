#pragma once
#include <GameEngineBase/GameEngineTime.h>

// GameEngineObject�� ��ӹ޴� class���� �������� ������.
// virtual�� ����� �Լ����� ����Ҽ��ְ� ���Ҽ����ִ� ������ �޴´�.
class GameEngineObject
{
	friend class GameEngineLevel;
	friend class GameEngineCore;

public:
    GameEngineObject();
	virtual ~GameEngineObject();

	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	// �����ϰ�.
	virtual void Start() {}

	// �ൿ�Ѱ�.
	virtual void Update(float _Delta){}

	// �׷�����.
	virtual void Render(float _Delta) {}

	// �����ȴ�.
	virtual void Release() {}
	// ������Ʈ ��
	virtual void On()
	{
		IsUpdateValue = true;
	}
	// ������Ʈ ����
	virtual void Off()
	{
		IsUpdateValue = false;
	}
	// �������� ����
	void Death()
	{
		IsDeathValue = true;
	}
	// �����Ͱ� �׾������ʰ� ������Ʈ ���̸� true ���. <== �̷��߸� ������Ʈ ����.
	virtual bool IsUpdate()
	{
		return true == IsUpdateValue && false == IsDeathValue; // Death�λ����̸� ������Ʈ �ϸ�ȵ�.
	}
	// �׾������� Ȯ��.
	virtual bool IsDeath()
	{
		return IsDeathValue;
	}

	float GetLiveTime()
	{
		return LiveTime;
	}

	void ResetLiveTime()
	{
		LiveTime = 0.0f;
	}

	int GetOrder()
	{
		return Order;
	}

	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}


protected:


private:
	int Order = 0;
	bool IsUpdateValue = true; // �̰� false�� ����� �˴ϴ�.
	bool IsDeathValue = false; // �ƿ� �޸𸮿��� ���������� �;�.

	float LiveTime = 0.0f;

	// ���ʵ��� �־���, ���ʵڿ� ~~���ض� � �̿��ϱ� ���� LiveTime��
	void AddLiveTime(float _DeltaTime)
	{
		LiveTime += _DeltaTime;
	}
	
};

