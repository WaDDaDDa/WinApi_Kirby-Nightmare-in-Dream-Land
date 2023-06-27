#include "BurningMonster.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "Bullet.h"
#include "Kirby.h"

void BurningMonster::IdleStart()
{
	ChangeAnimationState("Idle");
}

void BurningMonster::IdleUpdate(float _Delta)
{
	GroundCheck(_Delta);
	if (GetLiveTime() >= 2.0f)
	{
		ChangeState(BurningMonsterState::Walk);
	}

	int Value = GameEngineRandom::MainRandom.RandomInt(0, 1);
	float Posi = Kirby::GetMainPlayer()->GetPos().X - GetPos().X;
	if (Posi <= 0 && BurningMonsterDir::Left == Dir)
	{
		ChangeState(BurningMonsterState::AttackStart);
		return;
	}
	if (Posi >= 0 && BurningMonsterDir::Right == Dir)
	{
		ChangeState(BurningMonsterState::AttackStart);
		return;
	}
}

void BurningMonster::WalkStart()
{
	AttackCollision->Off();
	ChangeAnimationState("Walk");
}

void BurningMonster::WalkUpdate(float _Delta)
{
	GroundCheck(_Delta);
	Movement(_Delta);

	if (GetLiveTime() >= 2.0f)
	{
		ChangeState(BurningMonsterState::Idle);
		return;
	}
}

void BurningMonster::HitReadyStart()
{
	AttackCollision->Off();
	BodyCollision->Off();
	DeathCollision->On();
	ChangeAnimationState("HitReady");
}

void BurningMonster::HitReadyUpdate(float _Delta)
{
	GroundCheck(_Delta);
	if (GetLiveTime() >= 1.0f)
	{
		MainRenderer->On();
		ChangeState(BurningMonsterState::Hit);
		return;
	}
}

void BurningMonster::HitStart()
{
	AttackCollision->Off();
	ChangeAnimationState("Hit");
}

void BurningMonster::HitUpdate(float _Delta)
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

void BurningMonster::DamageStart()
{
	AttackCollision->Off();

	float XValue = 0.0f;
	float YValue = 0.0f;
	// 오른쪽일때
	if (Dir == BurningMonsterDir::Right)
	{
		XValue = GameEngineRandom::MainRandom.RandomFloat(-250.0f, -50.0f);
		YValue = GameEngineRandom::MainRandom.RandomFloat(-700.0f, -100.0f);

	} // 왼쪽일때
	else if (Dir == BurningMonsterDir::Left)
	{
		XValue = GameEngineRandom::MainRandom.RandomFloat(50.0f, 250.0f);
		YValue = GameEngineRandom::MainRandom.RandomFloat(-700.0f, -100.0f);
	}
	ChangeAnimationState("Damage");
	SetGravityVector(float4{ XValue, YValue });
}

void BurningMonster::DamageUpdate(float _Delta)
{
	Gravity(_Delta);
	float4 MoveDir = float4::ZERO;
	if (BurningMonsterDir::Left == Dir)
	{
		MoveDir = float4::RIGHT;
	}
	else if (BurningMonsterDir::Right == Dir)
	{
		MoveDir = float4::LEFT;
	}
	// 벽판정
	if (Dir == BurningMonsterDir::Right)
	{
		CheckPos = { -40.0f, -40.0f };
		// 벽판정
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MoveDir.X *= 0;
		}
	}
	else if (Dir == BurningMonsterDir::Left)
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
		ChangeState(BurningMonsterState::Effect);
		return;
	}
}

void BurningMonster::EffectStart()
{
	Kirby::GetMainPlayer()->AddScore();
	AddPos(CollisionPos);
	BodyCollision->Off();
	ChangeAnimationState("Effect");
}

void BurningMonster::EffectUpdate(float _Delta)
{
	if (0.5f <= GetLiveTime())
	{
		Death();
	}
}

void BurningMonster::AttackStartStart()
{
	ChangeAnimationState("AttackStart");
}

void BurningMonster::AttackStartUpdate(float _Delta)
{
	if (0.5f <= GetLiveTime())
	{
		int Value = 1;
		float Posi = Kirby::GetMainPlayer()->GetPos().X - GetPos().X;
		if (Posi <= 0 && BurningMonsterDir::Left == Dir)
		{
			Value = 2;
			if (Posi >= -AttRange)
			{
				Value = 1;
			}
		}
		else if (Posi >= 0 && BurningMonsterDir::Right == Dir)
		{
			Value = 2;
			if (Posi <= AttRange)
			{
				Value = 1;
			}
		}

		switch (Value)
		{
		case 1:
			ChangeState(BurningMonsterState::Attack1);
			return;
		case 2:
			ChangeState(BurningMonsterState::Attack2);
			return;
		default:
			break;
		}
	}
}

// 불뿜기.
void BurningMonster::Attack1Start()
{
	AttackCollision->On();
	if (BurningMonsterDir::Left == GetDir())
	{
		LeftAttackRenderer->On();
		LeftAttack2Renderer->On();
	}
	else if (BurningMonsterDir::Right == GetDir())
	{
		RightAttackRenderer->On();
		RightAttack2Renderer->On();
	}

	ChangeAnimationState("Attack1");
}

void BurningMonster::Attack1Update(float _Delta)
{
	GroundCheck(_Delta);

	if (GetLiveTime() >= 1.0f)
	{
		LeftAttackRenderer->Off();
		LeftAttack2Renderer->Off();
		RightAttackRenderer->Off();
		RightAttack2Renderer->Off();
		AttackCollision->Off();
		ChangeState(BurningMonsterState::Walk);
		return;
	}

	if (BurningMonsterDir::Left == Dir)
	{
		AttackCollision->SetCollisionPos({ -AttackCollisionPos.X , AttackCollisionPos.Y });
	}
	else if (BurningMonsterDir::Right == Dir)
	{
		AttackCollision->SetCollisionPos(AttackCollisionPos);
	}
}

// 불 발사
void BurningMonster::Attack2Start()
{
	Bullet* StarAttack = GetLevel()->CreateActor<Bullet>();
	StarAttack->SetPos(GetPos() + float4{0,-40});
	StarAttack->SetMaster(this);
	StarAttack->Init();

	ChangeAnimationState("Attack2");
}

void BurningMonster::Attack2Update(float _Delta)
{
	GroundCheck(_Delta);

	if (GetLiveTime() >= 0.5f)
	{
		LeftAttackRenderer->Off();
		LeftAttack2Renderer->Off();
		RightAttackRenderer->Off();
		RightAttack2Renderer->Off();
		AttackCollision->Off();
		ChangeState(BurningMonsterState::Walk);
		return;
	}

	if (BurningMonsterDir::Left == Dir)
	{
		AttackCollision->SetCollisionPos({ -AttackCollisionPos.X , AttackCollisionPos.Y });
	}
	else if (BurningMonsterDir::Right == Dir)
	{
		AttackCollision->SetCollisionPos(AttackCollisionPos);
	}
}