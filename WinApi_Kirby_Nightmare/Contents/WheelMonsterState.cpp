#include "WheelMonster.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "Kirby.h"

void WheelMonster::IdleStart()
{
	ChangeAnimationState("Idle");
}

void WheelMonster::IdleUpdate(float _Delta)
{
	GroundCheck(_Delta);
	if (GetLiveTime() >= 1.0f)
	{
		ChangeState(WheelMonsterState::Walk);
		return;
	}
}

void WheelMonster::WalkStart()
{
	ChangeAnimationState("Walk");
}

void WheelMonster::WalkUpdate(float _Delta)
{
	GroundCheck(_Delta);
	Movement(_Delta);
	if (GetLiveTime() >= 4.0f)
	{
		ChangeState(WheelMonsterState::Idle);
		return;
	}
}

void WheelMonster::HitReadyStart()
{
	BodyCollision->Off();
	DeathCollision->On();
	ChangeAnimationState("HitReady");
}

void WheelMonster::HitReadyUpdate(float _Delta)
{
	GroundCheck(_Delta);
	if (GetLiveTime() >= 1.0f)
	{
		MainRenderer->On();
		ChangeState(WheelMonsterState::Hit);
		return;
	}
}

void WheelMonster::HitStart()
{
	ChangeAnimationState("Hit");
}

void WheelMonster::HitUpdate(float _Delta)
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

void WheelMonster::DamageStart()
{
	MainRenderer->SetScaleRatio(8.0f);
	float XValue = 0.0f;
	float YValue = 0.0f;
	// 오른쪽일때
	if (Dir == WheelMonsterDir::Right)
	{
		XValue = GameEngineRandom::MainRandom.RandomFloat(-250.0f, -50.0f);
		YValue = GameEngineRandom::MainRandom.RandomFloat(-700.0f, -100.0f);

	} // 왼쪽일때
	else if (Dir == WheelMonsterDir::Left)
	{
		XValue = GameEngineRandom::MainRandom.RandomFloat(50.0f, 250.0f);
		YValue = GameEngineRandom::MainRandom.RandomFloat(-700.0f, -100.0f);
	}
	ChangeAnimationState("Damage");
	SetGravityVector(float4{ XValue, YValue });
}

void WheelMonster::DamageUpdate(float _Delta)
{
	//GroundCheck(_Delta);
	Gravity(_Delta);
	float4 MoveDir = float4::ZERO;
	if (WheelMonsterDir::Left == Dir)
	{
		MoveDir = float4::RIGHT;
	}
	else if (WheelMonsterDir::Right == Dir)
	{
		MoveDir = float4::LEFT;
	}
	// 벽판정
	if (Dir == WheelMonsterDir::Right)
	{
		CheckPos = { -40.0f, -40.0f };
		// 벽판정
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MoveDir.X *= 0;
		}
	}
	else if (Dir == WheelMonsterDir::Left)
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
		ChangeState(WheelMonsterState::Effect);
		return;
	}
}

void WheelMonster::EffectStart()
{
	Kirby::GetMainPlayer()->AddScore();
	AddPos(CollisionPos);
	BodyCollision->Off();
	SoundEffect = GameEngineSound::SoundPlay("song102.wav");
	ChangeAnimationState("Effect");
}

void WheelMonster::EffectUpdate(float _Delta)
{
	// GroundCheck(_Delta);
	GravityOff();
	if (0.5f <= GetLiveTime())
	{
		Death();
	}
}
