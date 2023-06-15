#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"
#include <string>
#include <list>
#include <Contents/ContentsEnum.h>

class GameEngineLevel;
class GameEngineRenderer;
class GameEngineCollision;
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

	float4 GetPos()
	{
		return Pos;
	}

	// 이미지가 비어있는 렌더러를 생성하는 함수.
	// 이미지가 비어있기 때문에 출력시키려면 SetTexture를 통해 이미지를 연결시켜주어야 한다.
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

	template<typename EnumType>
	GameEngineRenderer* CreateUIRenderer(EnumType _Order)
	{
		return CreateUIRenderer("", static_cast<int>(_Order));
	}

	GameEngineRenderer* CreateUIRenderer(int _Order = 0)
	{
		return CreateUIRenderer("", static_cast<int>(_Order));
	}

	template<typename EnumType>
	GameEngineRenderer* CreateUIRenderer(const std::string& _ImageName, EnumType _Order)
	{
		return CreateUIRenderer(_ImageName, static_cast<int>(_Order));
	}

	GameEngineRenderer* CreateUIRenderer(const std::string& _ImageName, int _Order);



	template<typename EnumType>
	GameEngineCollision* CreateCollision(EnumType _Order)
	{
		return CreateCollision(static_cast<int>(_Order));
	}


	GameEngineCollision* CreateCollision(int _Order = 0);

	GameEngineLevel* GetLevel()
	{
		return Level;
	}

	bool IsLevelOver()
	{
		return IsOverValue;
	}

	void OverOn()
	{
		IsOverValue = true;
	}

	void OverOff()
	{
		IsOverValue = false;
	}

	Abillity GetAbillity()
	{
		return CurAbillity;
	}
	void SetAbillity(Abillity _abillity)
	{
		CurAbillity = _abillity;
	}

protected:
	virtual void LevelStart() {}
	virtual void LevelEnd() {}

private:
	// 레벨이 변경되었을때 엑터가 레벨이 변경되기전의 정보를 그대로가지고 레벨이 변경되는값이다.
	// false라면 레벨이 변경될때 이전의 플레이어는 사라지고.
	// true라면 그대로 유지된다.
	bool IsOverValue = false;

	float4 Pos = float4::ZERO;

	GameEngineLevel* Level;
	
	std::list<GameEngineRenderer*> AllRenderer;
	std::list<GameEngineCollision*> AllCollision;

	void ActorRelease();
	Abillity CurAbillity = Abillity::Normal;
};

