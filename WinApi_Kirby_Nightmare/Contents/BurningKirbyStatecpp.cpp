#include "BurningKirby.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "MainHubLevel.h"

void BurningKirby::DamageStart()
{
	//float4 PrevPos = GetMainPlayer()->GetPos();
	//GetMainPlayer()->Death();
	//SetMainPlayer(GetLevel()->CreateActor<Kirby>());
	//GetMainPlayer()->SetPos(PrevPos);
	//GetMainPlayer()->SetGroundTexture(GetGroundTexture());
	ChangeKirby(Abillity::Normal);
	GetMainPlayer()->DirCheck();
	GetMainPlayer()->ChangeState(KirbyState::Damage);
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
		ChangeState(KirbyState::Idle);
		return;
	}

	float4 TackleSpeed = { Speed * _Delta , 0.0f };
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
