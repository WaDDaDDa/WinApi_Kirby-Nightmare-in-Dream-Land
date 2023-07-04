#include "WheelKirby.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "MainHubLevel.h"
#include "WheelEffect.h"

void WheelKirby::DamageStart()
{
	ChangeKirby(Abillity::Normal);
	Kirby::GetMainPlayer()->DirCheck();
	Kirby::GetMainPlayer()->ChangeState(KirbyState::Damage);
	return;
}

void WheelKirby::AttackStartStart()
{
	SetGravityVector(float4::UP * 400.0f);
	ChangeAnimationState("AttackStart");
}

void WheelKirby::AttackStartUpdate(float _Delta)
{
	Gravity(_Delta);

	if (GetLiveTime() >= 0.45f)
	{
		ChangeState(KirbyState::Attack);
		return;
	}
}

void WheelKirby::AttackStart()
{
	BodyCollision->Off();
	AttCollision->On();
	CurDir = Dir;
	Speed *= 2;
	WhEffect = GetLevel()->CreateActor<WheelEffect>();
	ChangeAnimationState("Attack");
}

void WheelKirby::AttackUpdate(float _Delta)
{
	if (Dir != CurDir)
	{
		Speed *= 0.5;
		WhEffect->Death();
		ChangeState(KirbyState::DirChange);
		return;
	}

	GroundCheck(_Delta);
	Movement2(_Delta);

	if (true == GameEngineInput::IsDown('X'))
	{
		BodyCollision->On();
		AttCollision->Off();
		Speed *= 0.5;
		WhEffect->Death();
		ChangeState(KirbyState::Idle);
		return;
	}

	float4 AttackEnd = float4::ZERO;
	float4 AttackSpeed = { Speed * _Delta , 0.0f };

	if (KirbyDir::Left == Dir)
	{
		CheckPos = { -40.0f, -40.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			AttackEnd = float4::UP * 600.0f + float4::RIGHT * 200.0f;
			SetGravityVector(AttackEnd);
			Speed *= 0.5;
			AttCollision->Off();
			BodyCollision->On();
			SoundEffect.Stop();
			SoundEffect = GameEngineSound::SoundPlay("30 ºÒ ½ÃÀÛ´À³¦.wav");
			WhEffect->Death();
			ChangeState(KirbyState::Falling);
			return;
		}
		AddPos(-AttackSpeed);
	}
	else if (KirbyDir::Right == Dir)
	{
		CheckPos = { 40.0f, -40.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			AttackEnd = float4::UP * 600.0f + float4::LEFT * 200.0f;
			SetGravityVector(AttackEnd);
			Speed *= 0.5;
			AttCollision->Off();
			BodyCollision->On();
			SoundEffect.Stop();
			SoundEffect = GameEngineSound::SoundPlay("30 ºÒ ½ÃÀÛ´À³¦.wav");
			WhEffect->Death();
			ChangeState(KirbyState::Falling);
			return;
		}
		AddPos(AttackSpeed);
	}
}

/////

void WheelKirby::JumpAttackStartStart()
{
	SetGravityVector(float4::UP * 400.0f);
	ChangeAnimationState("JumpAttackStart");
}

void WheelKirby::JumpAttackStartUpdate(float _Delta)
{
	Gravity(_Delta);

	if (GetLiveTime() >= 0.45f)
	{
		ChangeState(KirbyState::Attack);
		return;
	}
}

void WheelKirby::JumpAttackStart()
{
	BodyCollision->Off();
	AttCollision->On();
	CurDir = Dir;
	Speed *= 2;
	ChangeAnimationState("JumpAttack");
}

void WheelKirby::JumpAttackUpdate(float _Delta)
{
	if (Dir != CurDir)
	{
		Speed *= 0.5;
		ChangeState(KirbyState::DirChange);
		return;
	}

	GroundCheck(_Delta);
	Movement2(_Delta);

	if (true == GameEngineInput::IsDown('X'))
	{
		BodyCollision->On();
		AttCollision->Off();
		Speed *= 0.5;
		ChangeState(KirbyState::Idle);
		return;
	}

	float4 AttackEnd = float4::ZERO;
	float4 AttackSpeed = { Speed * _Delta , 0.0f };

	if (KirbyDir::Left == Dir)
	{
		CheckPos = { -40.0f, -40.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			AttackEnd = float4::UP * 600.0f + float4::RIGHT * 200.0f;
			SetGravityVector(AttackEnd);
			Speed *= 0.5;
			AttCollision->Off();
			BodyCollision->On();
			SoundEffect.Stop();
			SoundEffect = GameEngineSound::SoundPlay("30 ºÒ ½ÃÀÛ´À³¦.wav");
			ChangeState(KirbyState::Falling);
			return;
		}
		AddPos(-AttackSpeed);
	}
	else if (KirbyDir::Right == Dir)
	{
		CheckPos = { 40.0f, -40.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			AttackEnd = float4::UP * 600.0f + float4::LEFT * 200.0f;
			SetGravityVector(AttackEnd);
			Speed *= 0.5;
			AttCollision->Off();
			BodyCollision->On();
			SoundEffect.Stop();
			SoundEffect = GameEngineSound::SoundPlay("30 ºÒ ½ÃÀÛ´À³¦.wav");
			ChangeState(KirbyState::Falling);
			return;
		}
		AddPos(AttackSpeed);
	}
}

void WheelKirby::DirChangeStart()
{
	ChangeAnimationState("DirChange");
}

void WheelKirby::DirChangeUpdate(float _Delta)
{
	GroundCheck(_Delta);
	if (GetLiveTime() >= 0.15f)
	{
		ChangeState(KirbyState::Attack);
		return;
	}
}