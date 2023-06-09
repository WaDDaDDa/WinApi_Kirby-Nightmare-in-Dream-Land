#include "BurningKirby.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "MainHubLevel.h"

void BurningKirby::DamageStart()
{
	ChangeKirby(Abillity::Normal);
	Kirby::GetMainPlayer()->DirCheck();
	Kirby::GetMainPlayer()->GetMainPlayer()->ChangeState(KirbyState::Damage);
	return;
}

void BurningKirby::AttackStartStart()
{
	Speed *= 2;
	AttackCollision->On();
	BodyCollision->Off();
	ChangeAnimationState("AttackStart");
}

void BurningKirby::AttackStart()
{
	SoundEffect = GameEngineSound::SoundPlay("song137.wav");
	ChangeAnimationState("Attack");
}

void BurningKirby::AttackStartUpdate(float _Delta)
{
	if (GetLiveTime() >= 0.1f)
	{
		ChangeState(KirbyState::Attack);
		return;
	}

	float4 TackleSpeed = { 0.0f , 0.0f };
	if (KirbyDir::Left == Dir)
	{
		CheckPos = { -40.0f, -40.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			AddPos(MovePos);
			return;
		}
		AddPos(-TackleSpeed);
	}
	else if (KirbyDir::Right == Dir)
	{
		CheckPos = { 40.0f, -40.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			AddPos(MovePos);
			return;
		}
		AddPos(TackleSpeed);
	}
}

void BurningKirby::AttackUpdate(float _Delta)
{

	if (GetLiveTime() >= 1.0f)
	{
		AttackCollision->Off();
		BodyCollision->On();
		Speed /= 2;
		SoundEffect.Stop();
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
			AttackEnd = float4::UP * 400.0f + float4::RIGHT * 200.0f;
			SetGravityVector(AttackEnd);
			Speed = NormalSpeed;
			AttackCollision->Off();
			BodyCollision->On();
			SoundEffect.Stop();
			SoundEffect = GameEngineSound::SoundPlay("30 �� ���۴���.wav");
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
			AttackEnd = float4::UP * 400.0f + float4::LEFT * 200.0f;
			SetGravityVector(AttackEnd);
			Speed = NormalSpeed;
			AttackCollision->Off();
			BodyCollision->On();
			SoundEffect.Stop();
			SoundEffect = GameEngineSound::SoundPlay("30 �� ���۴���.wav");
			ChangeState(KirbyState::Falling);
			return;
		}
		AddPos(AttackSpeed);
	}
}

void BurningKirby::JumpAttackStartStart()
{
	Speed *= 2;
	AttackCollision->On();
	BodyCollision->Off();
	ChangeAnimationState("AttackStart");
}

void BurningKirby::JumpAttackStart()
{
	ChangeAnimationState("Attack");
}

void BurningKirby::JumpAttackStartUpdate(float _Delta)
{
	if (GetLiveTime() >= 0.1f)
	{
		ChangeState(KirbyState::Attack);
		return;
	}

	float4 TackleSpeed = { 0.0f , 0.0f };
	if (KirbyDir::Left == Dir)
	{
		CheckPos = { -40.0f, -40.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			AddPos(MovePos);
			return;
		}
		AddPos(-TackleSpeed);
	}
	else if (KirbyDir::Right == Dir)
	{
		CheckPos = { 40.0f, -40.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			AddPos(MovePos);
			return;
		}
		AddPos(TackleSpeed);
	}
}

void BurningKirby::JumpAttackUpdate(float _Delta)
{

	if (GetLiveTime() >= 1.0f)
	{
		AttackCollision->Off();
		BodyCollision->On();
		Speed /= 2;
		ChangeState(KirbyState::Idle);
		return;
	}

	float4 AttackSpeed = { Speed * _Delta , 0.0f };
	if (KirbyDir::Left == Dir)
	{
		CheckPos = { -40.0f, -40.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			AddPos(MovePos);
			return;
		}
		AddPos(-AttackSpeed);
	}
	else if (KirbyDir::Right == Dir)
	{
		CheckPos = { 40.0f, -40.0f };
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
			AddPos(MovePos);
			return;
		}
		AddPos(AttackSpeed);
	}
}

void BurningKirby::TackleStart()
{
	SoundEffect = GameEngineSound::SoundPlay("song173.wav");
	TackleCollision->On();
	Kirby::GetMainPlayer()->Speed = TackleSpeed;
	ChangeAnimationState("Tackle");
}
