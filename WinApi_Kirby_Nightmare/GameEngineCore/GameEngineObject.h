#pragma once

// GameEngineObject�� ��ӹ޴� class���� �������� ������.
// virtual�� ����� �Լ����� ����Ҽ��ְ� ���Ҽ����ִ� ������ �޴´�.
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

	// �����ϰ�.
	virtual void Start() {}

	// �ൿ�Ѱ�.
	virtual void Update(float _Delta) {}

	// �׷�����.
	virtual void Render() {}

	// �����ȴ�.
	virtual void Release() {}
	// ������Ʈ ��
	void On()
	{
		IsUpdateValue = true;
	}
	// ������Ʈ ����
	void Off()
	{
		IsUpdateValue = false;
	}
	// �������� ����
	void Death()
	{
		IsDeathValue = true;
	}
	// �����Ͱ� �׾������ʰ� ������Ʈ ���̸� true ���. <== �̷��߸� ������Ʈ ����.
	bool IsUpdate()
	{
		return true == IsUpdateValue && false == IsDeathValue; // Death�λ����̸� ������Ʈ �ϸ�ȵ�.
	}
	// �׾������� Ȯ��.
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
	bool IsUpdateValue = true; // �̰� false�� ����� �˴ϴ�.
	bool IsDeathValue = false; // �ƿ� �޸𸮿��� ���������� �;�.

	float LiveTime = 0.0f;

	void AddLiveTime(float _DeltaTime)
	{
		LiveTime += _DeltaTime;
	}
	
};

