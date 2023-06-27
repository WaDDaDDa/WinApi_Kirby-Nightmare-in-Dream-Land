#include "WaddleDee.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "Kirby.h"

void WaddleDee::IdleStart()
{
	ChangeAnimationState("Idle");
}

void WaddleDee::IdleUpdate(float _Delta)
{
	GroundCheck(_Delta);
	if (GetLiveTime() >= 1.0f)
	{
		ChangeState(WaddleDeeState::Walk);
		return;
	}
}

void WaddleDee::WalkStart()
{
	ChangeAnimationState("Walk");
}

void WaddleDee::WalkUpdate(float _Delta)
{
	GroundCheck(_Delta);
	Movement(_Delta);
	if (GetLiveTime() >= 4.0f)
	{
		ChangeState(WaddleDeeState::Idle);
		return;
	}
}

void WaddleDee::HitReadyStart()
{
	BodyCollision->Off();
	DeathCollision->On();
	ChangeAnimationState("HitReady");
}

void WaddleDee::HitReadyUpdate(float _Delta)
{
	GroundCheck(_Delta);
	if (GetLiveTime() >= 1.0f)
	{
		MainRenderer->On();
		ChangeState(WaddleDeeState::Hit);
		return;
	}
}

void WaddleDee::HitStart()
{
	ChangeAnimationState("Hit");
}

void WaddleDee::HitUpdate(float _Delta)
{
	GroundCheck(_Delta);
	float4 MoveDir = Actor->GetPos() - GetPos();
	MoveDir.Normalize();
	AddPos(MoveDir * 800.0f* _Delta);

	if (GetLiveTime() >= 0.2f)
	{
		Death();
		return;
	}
}

void WaddleDee::DamageStart()
{
	MainRenderer->SetScaleRatio(8.0f);
	float XValue = 0.0f;
	float YValue = 0.0f;
	// 오른쪽일때
	if (Dir == WaddleDeeDir::Right)
	{
		XValue = GameEngineRandom::MainRandom.RandomFloat(-250.0f, -50.0f);
		YValue = GameEngineRandom::MainRandom.RandomFloat(-700.0f, -100.0f);

	} // 왼쪽일때
	else if (Dir == WaddleDeeDir::Left)
	{
		XValue = GameEngineRandom::MainRandom.RandomFloat(50.0f, 250.0f);
		YValue = GameEngineRandom::MainRandom.RandomFloat(-700.0f, -100.0f);
	}
	ChangeAnimationState("Damage");
	SetGravityVector(float4{ XValue, YValue });
}

void WaddleDee::DamageUpdate(float _Delta)
{
	//GroundCheck(_Delta);
	Gravity(_Delta);
	float4 MoveDir = float4::ZERO;
	if (WaddleDeeDir::Left == Dir)
	{
		MoveDir = float4::RIGHT;
	}
	else if (WaddleDeeDir::Right == Dir)
	{
		MoveDir = float4::LEFT;
	}
	// 벽판정
	if (Dir == WaddleDeeDir::Right)
	{
		CheckPos = { -40.0f, -40.0f };
		// 벽판정
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MoveDir.X *= 0;
		}
	}
	else if (Dir == WaddleDeeDir::Left)
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
		ChangeState(WaddleDeeState::Effect);
		return;
	}
}

void WaddleDee::EffectStart()
{
	Kirby::GetMainPlayer()->AddScore();
	AddPos(CollisionPos);
	BodyCollision->Off();
	ChangeAnimationState("Effect");
}

void WaddleDee::EffectUpdate(float _Delta)
{
	// GroundCheck(_Delta);
	GravityOff();
	if (0.5f <= GetLiveTime())
	{
		Death();
	}
}
