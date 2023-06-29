#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "BurningMonster.h"
#include <GameEnginePlatform/GameEngineSound.h>

enum class BulletState
{
	Normal,
	Bomb,
	Max, // 일반적으로 사용하지 않는 값.
};

// 설명 :
class Bullet : public GameEngineActor
{
public:
	Bullet();
	~Bullet();

	Bullet(const Bullet& _Other) = delete;
	Bullet(Bullet&& _Other) noexcept = delete;
	Bullet& operator=(const Bullet& _Other) = delete;
	Bullet& operator=(Bullet&& _Other) noexcept = delete;

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

	void SetMaster(BurningMonster* _Master)
	{
		Master = _Master;
	}
	void Init();

protected:
	void ChangeState(BulletState _State);
	void StateUpdate(float _Delta);

	void NormalStart();
	void NormalUpdate(float _Delta);
	void BombStart();
	void BombUpdate(float _Delta);

private:
	class GameEngineSoundPlayer SoundEffect;

	BurningMonster* Master = nullptr;
	GameEngineCollision* AttackCollision = nullptr;
	float4 AttackCollisionScale = float4{ 100,100 };

	float4 RightAttackPos = float4{ 40.0f, -40.0f };
	float4 LeftAttackPos = float4{ -40.0f, -40.0f };
	float4 Dir = float4::ZERO;
	float Speed = 800.0f;
	float4 DirVec = float4::ZERO;
	BulletState State = BulletState::Max;

	void Start() override;
	void Update(float _Delta) override;
};

