#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Kirby.h"

class Star : public GameEngineActor
{
public:
	Star();
	~Star();

	Star(const Star& _Other) = delete;
	Star(Star&& _Other) noexcept = delete;
	Star& operator=(const Star& _Other) = delete;
	Star& operator=(Star&& _Other) noexcept = delete;

	class GameEngineRenderer* Renderer;

	void SetDir(const float4& _Dir)
	{
		Dir = _Dir;
	}

	void SetSpeed(const float _Speed)
	{
		Speed = _Speed;
	}

	void SetKirby(Kirby* _Kirby)
	{
		MainKirby = _Kirby;
	}

	Kirby* GetKirby()
	{
		return MainKirby;
	}

	void DirCheck();

protected:

private:
	GameEngineCollision* AttackCollision = nullptr;
	float4 AttackCollisionScale = float4{ 100,100 };

	float4 RightAttackPos = float4{ 40.0f, -40.0f };
	float4 LeftAttackPos = float4{ -40.0f, -40.0f };
	Kirby* MainKirby = nullptr;
	float4 Dir = float4::ZERO;
	float Speed = 600.0f;

	void Start() override;
	void Update(float _Delta) override;
};

