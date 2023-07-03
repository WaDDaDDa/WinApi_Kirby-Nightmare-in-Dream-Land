#include "WheelKirby.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "MainHubLevel.h"

void WheelKirby::DamageStart()
{
	ChangeKirby(Abillity::Normal);
	Kirby::GetMainPlayer()->DirCheck();
	Kirby::GetMainPlayer()->ChangeState(KirbyState::Damage);
	return;
}

void WheelKirby::AttackStartStart()
{
	ChangeAnimationState("AttackStart");
}

void WheelKirby::AttackStartUpdate(float _Delta)
{

}

void WheelKirby::AttackStart()
{

}

void WheelKirby::AttackUpdate(float _Delta)
{

}

/////

void WheelKirby::JumpAttackStartStart()
{
	ChangeAnimationState("JumpAttackStart");
}

void WheelKirby::JumpAttackStartUpdate(float _Delta)
{
	GroundCheck(_Delta);
}

void WheelKirby::JumpAttackStart()
{

}

void WheelKirby::JumpAttackUpdate(float _Delta)
{

}