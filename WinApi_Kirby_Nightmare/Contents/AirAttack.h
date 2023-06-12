#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Kirby.h"

class AirAttack : public GameEngineActor
{
public:
    AirAttack();
    ~AirAttack();

    AirAttack(const AirAttack& _Other) = delete;
    AirAttack(AirAttack&& _Other) noexcept = delete;
    AirAttack& operator=(const AirAttack& _Other) = delete;
    AirAttack& operator=(AirAttack&& _Other) noexcept = delete;

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


protected:

private:

	Kirby* MainKirby = nullptr;
	float4 Dir = float4::ZERO;
	float Speed = 200.0f;

	void Start() override;
	void Update(float _Delta) override;
};

