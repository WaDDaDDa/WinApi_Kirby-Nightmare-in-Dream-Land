#include "SwordKirby.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "MainHubLevel.h"

void SwordKirby::DamageStart()
{
	ChangeKirby(Abillity::Normal);
	Kirby::GetMainPlayer()->DirCheck();
	Kirby::GetMainPlayer()->ChangeState(KirbyState::Damage);
	return;
}

void SwordKirby::AttackStartStart()
{
	AttackCollision->On();
	//BodyCollision->Off();
	// 중력이 0이면 == 땅에 붙어있으면.  그외에는 공중이므로 공중공격.
	if (float4::ZERO != Kirby::GetMainPlayer()->GetGravityVector())
	{
		ChangeAnimationState("AttackStart");
		return;
	}
	else
	{
		ChangeAnimationState("JumpAttackStart");
		return;
	}
}

void SwordKirby::AttackStartUpdate(float _Delta)
{
	GroundCheck(_Delta);

	if (Dir == KirbyDir::Left)
	{
		//CameraFocus();
		CheckPos = { -40.0f, -40.0f };
		// 벽판정
		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
		}
		AddPos(MovePos);
	}
	else if (Dir == KirbyDir::Right)
	{
		//CameraFocus();
		CheckPos = { 40.0f, -40.0f };

		if (GetWallCheck() != RGB(255, 255, 255))
		{
			MovePos.X *= 0;
		}
		AddPos(MovePos);
	}

	if (GetLiveTime() >= 0.1f)
	{
		ChangeState(KirbyState::Attack);
		return;
	}
}

void SwordKirby::JumpAttackUpdate(float _Delta)
{
	
}

void SwordKirby::AttackStart()
{
	AttackCollision->On();
	AttRenderer->On();
	ChangeAnimationState("Attack");
}

void SwordKirby::AttackUpdate(float _Delta)
{
	GroundCheck(_Delta);

	//if (true == GameEngineInput::IsUp('X'))
	//{
	//	AttackCollision->Off();
	//	AttRenderer->Off();
	//	BodyCollision->On();
	//	ChangeState(KirbyState::Idle);
	//	return;
	//}

}
