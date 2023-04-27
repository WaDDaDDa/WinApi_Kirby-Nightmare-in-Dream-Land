#pragma once

// GameEngineObject�� ��ӹ޴� class���� �������� ������.
// virtual�� ����� �Լ����� ����Ҽ��ְ� ���Ҽ����ִ� ������ �޴´�.
class GameEngineObject
{
public:
    GameEngineObject();
    ~GameEngineObject();

    GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
    GameEngineObject& operator=(const GameEngineObject&& _Other) = delete;
    GameEngineObject(const GameEngineObject& _Other) = delete;
    GameEngineObject(const GameEngineObject&& _Other) = delete;

	// �����ϰ�.
	virtual void Start() {}

	// �ൿ�Ѱ�.
	virtual void Update() {}

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
	bool IsDeath()
	{
		return IsDeathValue;
	}

protected:


private:
	bool IsUpdateValue = true; // �̰� false�� ����� �˴ϴ�.
	bool IsDeathValue = false; // �ƿ� �޸𸮿��� ���������� �;�.

};

