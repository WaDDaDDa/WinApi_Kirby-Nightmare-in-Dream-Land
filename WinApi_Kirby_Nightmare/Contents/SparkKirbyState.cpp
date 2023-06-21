#include "SparkKirby.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
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

void SparkKirby::AttackStart()
{
	ChangeAnimationState("Attack");
}

void SparkKirby::AttackStartUpdate(float _Delta)
{
	if (GetLiveTime() >= 0.1f)
	{
		ChangeState(KirbyState::Attack);
		return;
	}

}

void SparkKirby::AttackUpdate(float _Delta)
{
	if (GetLiveTime() >= 1.0f)
	{
		AttackCollision->Off();
		BodyCollision->On();
		ChangeState(KirbyState::Idle);
		return;
	}
}
