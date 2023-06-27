#include "SparkMonster.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "Bullet.h"
#include "Kirby.h"

void SparkMonster::IdleStart()
{
	ChangeAnimationState("Idle");
}

void SparkMonster::IdleUpdate(float _Delta)
{
	GroundCheck(_Delta);
	if (GetLiveTime() >= 1.0f)
	{
		float Posi = Kirby::GetMainPlayer()->GetPos().X - GetPos().X;

		if (Posi >= -AttRange)
		{
			ChangeState(SparkMonsterState::AttackStart);
			return;
		}

		if (Posi <= AttRange)
		{
			ChangeState(SparkMonsterState::AttackStart);
			return;
		}

		//if (Posi <= 0 && SparkMonsterDir::Left == Dir)
		//{
		//	if (Posi >= -AttRange)
		//	{
		//		ChangeState(SparkMonsterState::AttackStart);
		//		return;
		//	}
		//}
		//else if (Posi >= 0 && SparkMonsterDir::Right == Dir)
		//{
		//	if (Posi <= AttRange)
		//	{
		//		ChangeState(SparkMonsterState::AttackStart);
		//		return;
		//	}
		//}
		ChangeState(SparkMonsterState::Walk);
		return;
	}
}

void SparkMonster::WalkStart()
{
	AttackCollision->Off();
	SetGravityVector(float4::UP * JumpPower);
	ChangeAnimationState("Walk");
}

void SparkMonster::WalkUpdate(float _Delta)
{
	Gravity(_Delta);
	GroundCheck(_Delta);
	Movement(_Delta);
	if (GetLiveTime() >= 0.5f)
	{
		ChangeState(SparkMonsterState::Idle);
		return;
	}
}

void SparkMonster::HitReadyStart()
{
	AttackCollision->Off();
	BodyCollision->Off();
	DeathCollision->On();
	ChangeAnimationState("HitReady");
}

void SparkMonster::HitReadyUpdate(float _Delta)
{
	GroundCheck(_Delta);
	if (GetLiveTime() >= 1.0f)
	{
		MainRenderer->On();
		ChangeState(SparkMonsterState::Hit);
		return;
	}
}

void SparkMonster::HitStart()
{
	AttackCollision->Off();
	AttRenderer->Off();
	ChangeAnimationState("Hit");
}

void SparkMonster::HitUpdate(float _Delta)
{
	GroundCheck(_Delta);
	float4 MoveDir = Actor->GetPos() - GetPos();
	MoveDir.Normalize();
	AddPos(MoveDir * 800.0f * _Delta);

	if (GetLiveTime() >= 0.2f)
	{
		Death();
		return;
	}
}

void SparkMonster::DamageStart()
{
	AttackCollision->Off();
	AttRenderer->Off();
	float XValue = 0.0f;
	float YValue = 0.0f;
	// 오른쪽일때
	if (Dir == SparkMonsterDir::Right)
	{
		XValue = GameEngineRandom::MainRandom.RandomFloat(-250.0f, -50.0f);
		YValue = GameEngineRandom::MainRandom.RandomFloat(-700.0f, -100.0f);

	} // 왼쪽일때
	else if (Dir == SparkMonsterDir::Left)
	{
		XValue = GameEngineRandom::MainRandom.RandomFloat(50.0f, 250.0f);
		YValue = GameEngineRandom::MainRandom.RandomFloat(-700.0f, -100.0f);
	}
	ChangeAnimationState("Damage");
	SetGravityVector(float4{ XValue, YValue });
}

void SparkMonster::DamageUpdate(float _Delta)
{
	//GroundCheck(_Delta);
	Gravity(_Delta);
	float4 MoveDir = float4::ZERO;
	if (SparkMonsterDir::Left == Dir)
	{
		MoveDir = float4::RIGHT;
	}
	else if (SparkMonsterDir::Right == Dir)
	{
		MoveDir = float4::LEFT;
	}
	// 벽판정
	if (Dir == SparkMonsterDir::Right)
	{
		CheckPos = { -40.0f, -40.0f };
		// 벽판정
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MoveDir.X *= 0;
		}
	}
	else if (Dir == SparkMonsterDir::Left)
	{
		CheckPos = { 40.0f, -40.0f };

		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MoveDir.X *= 0;
		}
	}

	MoveDir.Normalize();
	AddPos(MoveDir * 100.0f * _Delta);

	if (0.5f <= GetLiveTime())
	{
		ChangeState(SparkMonsterState::Effect);
		return;
	}
}

void SparkMonster::EffectStart()
{
	Kirby::GetMainPlayer()->AddScore();
	AddPos(CollisionPos);
	BodyCollision->Off();
	ChangeAnimationState("Effect");
}

void SparkMonster::EffectUpdate(float _Delta)
{

	if (0.5f <= GetLiveTime())
	{
		Death();
	}
}

void SparkMonster::AttackStartStart()
{
	ChangeAnimationState("AttackStart");
}

void SparkMonster::AttackStartUpdate(float _Delta)
{
	if (0.5f <= GetLiveTime())
	{
		ChangeState(SparkMonsterState::Attack);
	}
}

// 불뿜기.
void SparkMonster::AttackStart()
{
	AttackCollision->On();
	AttRenderer->On();
	ChangeAnimationState("Attack");
}

void SparkMonster::AttackUpdate(float _Delta)
{
	GroundCheck(_Delta);

	if (GetLiveTime() >= 2.0f)
	{
		AttackCollision->Off();
		AttRenderer->Off();
		ChangeState(SparkMonsterState::Walk);
		return;
	}
}
