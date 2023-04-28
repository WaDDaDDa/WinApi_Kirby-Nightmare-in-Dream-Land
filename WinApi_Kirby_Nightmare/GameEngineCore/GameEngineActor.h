#pragma once
#include <GameEngineCore/GameEngineObject.h>
#include <GameEngineBase/GameEngineMath.h>

// ȭ��ȿ� �����ϴ� ��� ��.  ��ǥ�� �ִٸ� ���ͷ� ǥ��.
class GameEngineActor : public GameEngineObject
{
public:
    GameEngineActor();
    ~GameEngineActor();

    GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
    GameEngineActor& operator=(const GameEngineActor&& _Other) = delete;
    GameEngineActor(const GameEngineActor& _Other) = delete;
    GameEngineActor(const GameEngineActor&& _Other) = delete;

	void SetPos(const float4& _Pos)
	{
		Pos = _Pos;
	}

	void AddPos(const float4& _Pos)
	{
		Pos += _Pos;
	}

	void SetScale(const float4& _Scale)
	{
		Scale = _Scale;
	}

	float4 GetPos()
	{
		return Pos;
	}

	float4 GetScale()
	{
		return Scale;
	}

protected:

private:
	float4 Pos;
	float4 Scale; // <= ũ��� �������� �ʿ� �����ϴ�.

};

