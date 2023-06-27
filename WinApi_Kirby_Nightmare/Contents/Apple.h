#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "Kirby.h"
#include <string>
#include "Monster.h"

enum class AppleState
{
	Idle,
	Ground,
	Falling,
	Effect,
	HitReady,
	Hit,
	Max,
};

class Apple : public Monster
{
public:
	Apple();
	~Apple();

	Apple(const Apple& _Other) = delete;
	Apple(Apple&& _Other) noexcept = delete;
	Apple& operator=(const Apple& _Other) = delete;
	Apple& operator=(Apple&& _Other) noexcept = delete;


	void ChangeAnimationState(const std::string& _StateName);

	void ChangeState(AppleState _State);

	void StateUpdate(float _Delta);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void GroundStart();
	void GroundUpdate(float _Delta);

	void FallingStart();
	void FallingUpdate(float _Delta);

	void EffectStart();
	void EffectUpdate(float _Delta);

	void HitReadyStart();
	void HitReadyUpdate(float _Delta);

	void HitStart();
	void HitUpdate(float _Delta);

protected:

private:
	class GameEngineRenderer* Renderer = nullptr;
	class GameEngineCollision* BodyCollision = nullptr;
	class GameEngineCollision* DeathCollision = nullptr;

	float4 BodyCollisionScale = float4{ 80,80 };
	float4 DeathCollisionScale = float4{ 100, 100 };

	std::string CurState = "";

	AppleState State = AppleState::Max;

	void Start() override;
	
	void Update(float _Delta) override;

	GameEngineActor* Actor = nullptr;
};

