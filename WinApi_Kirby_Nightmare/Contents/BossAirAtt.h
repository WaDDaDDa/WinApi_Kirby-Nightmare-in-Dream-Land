#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BossMonster.h"

enum class BossAirAttState
{
	Normal,
	Bomb,
	Max, // 일반적으로 사용하지 않는 값.
};

// 설명 :
class BossAirAtt : public GameEngineActor
{
public:
	BossAirAtt();
	~BossAirAtt();

	BossAirAtt(const BossAirAtt& _Other) = delete;
	BossAirAtt(BossAirAtt&& _Other) noexcept = delete;
	BossAirAtt& operator=(const BossAirAtt& _Other) = delete;
	BossAirAtt& operator=(BossAirAtt&& _Other) noexcept = delete;

	class GameEngineRenderer* Renderer = nullptr;

	void SetDir(const float4& _Dir)
	{
		Dir = _Dir;
	}

	void SetSpeed(const float _Speed)
	{
		Speed = _Speed;
	}

	void DirCheck();

	void SetMaster(BossMonster* _Master)
	{
		Master = _Master;
	}
	void Init();

protected:
	void ChangeState(BossAirAttState _State);
	void StateUpdate(float _Delta);

	void NormalStart();
	void NormalUpdate(float _Delta);
	void BombStart();
	void BombUpdate(float _Delta);

private:
	BossMonster* Master = nullptr;
	GameEngineCollision* AttackCollision = nullptr;
	float4 AttackCollisionScale = float4{ 80,80 };

	float4 RightAttackPos = float4{ 40.0f, -40.0f };
	float4 LeftAttackPos = float4{ -40.0f, -40.0f };
	float4 Dir = float4::ZERO;
	float Speed = 400.0f;
	float4 DirVec = float4::ZERO;
	BossAirAttState State = BossAirAttState::Max;

	void Start() override;
	void Update(float _Delta) override;
};

