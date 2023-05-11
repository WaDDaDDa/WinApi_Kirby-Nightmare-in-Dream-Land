#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"
#include <string>
#include <list>

class GameEngineLevel;
class GameEngineRenderer;

// ȭ��ȿ� �����ϴ� ��� ��.  ��ǥ�� �ִٸ� ���ͷ� ǥ��.
class GameEngineActor : public GameEngineObject
{
	friend GameEngineLevel;
public:
    GameEngineActor();
	// ��ĳ���� ���� �Ҹ��� ȣ���� �ȵǴ� ��� ����.
	virtual ~GameEngineActor();

	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	void SetPos(const float4& _Pos)
	{
		Pos = _Pos;
	}

	void AddPos(const float4& _Pos)
	{
		Pos += _Pos;
	}

	float4 GetPos()
	{
		return Pos;
	}

	// �̹����� ����ִ� �������� �����ϴ� �Լ�.
	// �̹����� ����ֱ� ������ ��½�Ű���� SetTexture�� ���� �̹����� ��������־�� �Ѵ�.
	template<typename EnumType>
	GameEngineRenderer* CreateRenderer(EnumType _Order)
	{
		return CreateRenderer("", static_cast<int>(_Order));
	}

	GameEngineRenderer* CreateRenderer(int _Order = 0)
	{
		return CreateRenderer("", static_cast<int>(_Order));
	}

	template<typename EnumType>
	GameEngineRenderer* CreateRenderer(const std::string& _ImageName, EnumType _Order)
	{
		return CreateRenderer(_ImageName, static_cast<int>(_Order));
	}

	GameEngineRenderer* CreateRenderer(const std::string& _ImageName, int _Order);

	GameEngineLevel* GetLevel()
	{
		return Level;
	}

protected:

private:
	float4 Pos = float4::ZERO;

	GameEngineLevel* Level;
	
	std::list<GameEngineRenderer*> AllRenderer;

	// void PushMainCameraRenderer(GameEngineRenderer*);

	void ActorRelease();
};

