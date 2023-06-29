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
	ChangeAnimationState("AttackStart");
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

void SwordKirby::AttackStart()
{
	SoundEffect = GameEngineSound::SoundPlay("song147.wav");

	if (KirbyDir::Left == Kirby::GetMainPlayer()->GetDir())
	{
		LeftAttackCollision->On();
		LeftAttRenderer->ChangeAnimation("LeftSwordEffect");
	}
	else if (KirbyDir::Right == Kirby::GetMainPlayer()->GetDir())
	{
		RightAttackCollision->On();
		RightAttRenderer->ChangeAnimation("RightSwordEffect");
	}
	ChangeAnimationState("Attack");
}

void SwordKirby::AttackUpdate(float _Delta)
{
	GroundCheck(_Delta);

	if (GetLiveTime() >= 0.3f)
	{
		RightAttackCollision->Off();
		LeftAttackCollision->Off();
		RightAttRenderer->ChangeAnimation("RightSwordBlank");
		LeftAttRenderer->ChangeAnimation("LeftSwordBlank");
		ChangeState(KirbyState::Idle);
		return;
	}
}

/////

void SwordKirby::JumpAttackStartStart()
{

	ChangeAnimationState("JumpAttackStart");
}

void SwordKirby::JumpAttackStartUpdate(float _Delta)
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
		ChangeState(KirbyState::JumpAttack);
		return;
	}
}

void SwordKirby::JumpAttackStart()
{
	JumpAttackCollision->On();
	BodyCollision->Off();

	ChangeAnimationState("JumpAttack");
}

void SwordKirby::JumpAttackUpdate(float _Delta)
{
	GroundCheck(_Delta);
	Movement(_Delta);
	if (GetLiveTime() >= 0.5f)
	{
		JumpAttackCollision->Off();
		BodyCollision->On();
		ChangeState(KirbyState::Idle);
		return;
	}
}

void SwordKirby::TackleStart()
{
	SoundEffect = GameEngineSound::SoundPlay("song173.wav");
	TackleCollision->On();
	Kirby::GetMainPlayer()->Speed = TackleSpeed;
	ChangeAnimationState("Tackle");
}
