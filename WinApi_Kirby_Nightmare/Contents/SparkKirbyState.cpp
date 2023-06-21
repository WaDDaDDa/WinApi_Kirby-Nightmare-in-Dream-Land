#include "SparkKirby.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "MainHubLevel.h"

void SparkKirby::DamageStart()
{
	ChangeKirby(Abillity::Normal);
	Kirby::GetMainPlayer()->DirCheck();
	Kirby::GetMainPlayer()->ChangeState(KirbyState::Damage);
	return;
}

void SparkKirby::AttackStartStart()
{
	AttackCollision->On();
	BodyCollision->Off();
	ChangeAnimationState("AttackStart");
}

void SparkKirby::AttackStartUpdate(float _Delta)
{
	GroundCheck(_Delta);

	if (Dir == KirbyDir::Left)
	{
		//CameraFocus();
		CheckPos = { -40.0f, -40.0f };
		// º®ÆÇÁ¤
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

	if (true == GameEngineInput::IsUp('X'))
	{
		ChangeState(KirbyState::Idle);
		return;
	}
}

void SparkKirby::AttackStart()
{
	AttackCollision->On();
	AttRenderer->On();
	ChangeAnimationState("Attack");
}

void SparkKirby::AttackUpdate(float _Delta)
{
	GroundCheck(_Delta);

	if (true == GameEngineInput::IsUp('X'))
	{
		AttackCollision->Off();
		AttRenderer->Off();
		ChangeState(KirbyState::Idle);
		return;
	}

}
