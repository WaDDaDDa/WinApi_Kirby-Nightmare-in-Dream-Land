#pragma once
#include <GameEngineCore/GameEngineObject.h>
#include <GameEngineBase/GameEngineMath.h>

// 화면안에 존재하는 모든 것.  좌표가 있다면 엑터로 표현.
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
	float4 Scale; // <= 크기는 액터한테 필요 없습니다.

};

