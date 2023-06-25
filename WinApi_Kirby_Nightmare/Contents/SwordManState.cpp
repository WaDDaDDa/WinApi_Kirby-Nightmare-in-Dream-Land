#include "SwordMan.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "Bullet.h"
#include "Kirby.h"

void SwordMan::IdleStart()
{
	ChangeAnimationState("Idle");
}

void SwordMan::IdleUpdate(float _Delta)
{
	GroundCheck(_Delta);

	if (2.0f <= GetLiveTime())
	{
		int Value = 0;
		float Posi = Kirby::GetMainPlayer()->GetPos().X - GetPos().X;
		if (Posi <= 0 && SwordManDir::Left == Dir)
		{
			if (Posi >= -AttRange)
			{
				Value = 1;
			}
		}
		else if (Posi >= 0 && SwordManDir::Right == Dir)
		{
			if (Posi <= AttRange)
			{
				Value = 1;
			}
		}

		switch (Value)
		{
		case 1:
			ChangeState(SwordManState::AttackStart);
			return;
		default:
			ChangeState(SwordManState::Walk);
			break;
		}
	}
}

void SwordMan::WalkStart()
{
	ChangeAnimationState("Walk");
}

void SwordMan::WalkUpdate(float _Delta)
{
	GroundCheck(_Delta);
	Movement(_Delta);

	if (2.0f <= GetLiveTime())
	{
		ChangeState(SwordManState::Idle);
		return;
	}

	if (1.0f <= GetLiveTime())
	{
		int Value = 0;
		float Posi = Kirby::GetMainPlayer()->GetPos().X - GetPos().X;
		if (Posi <= 0 && SwordManDir::Left == Dir)
		{
			if (Posi >= -AttRange)
			{
				Value = 1;
			}
		}
		else if (Posi >= 0 && SwordManDir::Right == Dir)
		{
			if (Posi <= AttRange)
			{
				Value = 1;
			}
		}

		switch (Value)
		{
		case 1:
			ChangeState(SwordManState::AttackStart);
			return;
		default:
			break;
		}
	}
}

void SwordMan::HitReadyStart()
{
	RightAttackCollision->Off();
	LeftAttackCollision->Off();
	BodyCollision->Off();
	DeathCollision->On();
	ChangeAnimationState("HitReady");
}

void SwordMan::HitReadyUpdate(float _Delta)
{
	GroundCheck(_Delta);
	if (GetLiveTime() >= 1.0f)
	{
		MainRenderer->On();
		ChangeState(SwordManState::Hit);
		return;
	}
}

void SwordMan::HitStart()
{
	RightAttackCollision->Off();
	LeftAttackCollision->Off();
	ChangeAnimationState("Hit");
}

void SwordMan::HitUpdate(float _Delta)
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

void SwordMan::DamageStart()
{
	RightAttackCollision->Off();
	LeftAttackCollision->Off();

	float XValue = 0.0f;
	float YValue = 0.0f;
	// 오른쪽일때
	if (Dir == SwordManDir::Right)
	{
		XValue = GameEngineRandom::MainRandom.RandomFloat(-250.0f, -50.0f);
		YValue = GameEngineRandom::MainRandom.RandomFloat(-700.0f, -100.0f);
		
	} // 왼쪽일때
	else if (Dir == SwordManDir::Left)
	{
		XValue = GameEngineRandom::MainRandom.RandomFloat(50.0f, 250.0f);
		YValue = GameEngineRandom::MainRandom.RandomFloat(-700.0f, -100.0f);
	}
	ChangeAnimationState("Damage");
	SetGravityVector(float4{ XValue, YValue });
}

void SwordMan::DamageUpdate(float _Delta)
{
	//GroundCheck(_Delta);
	Gravity(_Delta);
	float4 MoveDir = float4::ZERO;
	if (SwordManDir::Left == Dir)
	{
		MoveDir = float4::RIGHT;
	}
	else if (SwordManDir::Right == Dir)
	{
		MoveDir = float4::LEFT;
	}
	// 벽판정
	if (Dir == SwordManDir::Right)
	{
		CheckPos = { -40.0f, -40.0f };
		// 벽판정
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MoveDir.X *= 0;
		}
	}
	else if (Dir == SwordManDir::Left)
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
		ChangeState(SwordManState::Effect);
		return;
	}
}

void SwordMan::EffectStart()
{
	Kirby::GetMainPlayer()->AddScore();
	AddPos(CollisionPos);
	BodyCollision->Off();
	ChangeAnimationState("Effect");
}

void SwordMan::EffectUpdate(float _Delta)
{
	//GroundCheck(_Delta);
	//GravityOff();
	if (0.5f <= GetLiveTime())
	{
		Death();
	}
}

void SwordMan::AttackStartStart()
{
	ChangeAnimationState("AttackStart");
}

void SwordMan::AttackStartUpdate(float _Delta)
{
	if (GetLiveTime() >= 1.0f)
	{
		RightAttackCollision->Off();
		LeftAttackCollision->Off();
		ChangeState(SwordManState::Attack);
		return;
	}
}

// 돌진 공격.
void SwordMan::AttackStart()
{
	if (SwordManDir::Left == GetDir())
	{
		LeftAttackCollision->On();
	}
	else if (SwordManDir::Right == GetDir())
	{
		RightAttackCollision->On();
	}

	ChangeAnimationState("Attack");
}

void SwordMan::AttackUpdate(float _Delta)
{
	GroundCheck(_Delta);

	if (SwordManDir::Left == GetDir())
	{
		AddPos(float4::LEFT * _Delta * Speed * 2.0f);
	}
	else if (SwordManDir::Right == GetDir())
	{
		AddPos(float4::RIGHT * _Delta * Speed * 2.0f);
	}

	if (GetLiveTime() >= 0.4f)
	{
		RightAttackCollision->Off();
		LeftAttackCollision->Off();
		ChangeState(SwordManState::Walk);
		return;
	}

}
