#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"
#include <string>
#include <list>

class GameEngineLevel;
class GameEngineRenderer;

// 화면안에 존재하는 모든 것.  좌표가 있다면 엑터로 표현.
class GameEngineActor : public GameEngineObject
{
	friend GameEngineLevel;
public:
    GameEngineActor();
	// 업캐스팅 관련 소멸자 호출이 안되는 경우 방지.
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

	GameEngineRenderer* CreateRenderer(const std::string& _ImageName);

	GameEngineLevel* GetLevel()
	{
		return Level;
	}

protected:

private:
	float4 Pos = float4::ZERO;
	float4 Scale = float4::ZERO; // <= 크기는 액터한테 필요 없습니다.

	GameEngineLevel* Level;

	std::list<GameEngineRenderer*> AllRenderer;

	void PushMainCameraRenderer(GameEngineRenderer*);
};

