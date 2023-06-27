#include "BossMonster.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Kirby.h"
#include "BossAirAtt.h"
#include "Apple.h"

void BossMonster::IdleStart()
{
	ChangeAnimationState("BossMonster_Idle");
}

void BossMonster::IdleUpdate(float _Delta)
{
	if (5.0f <= GetLiveTime())
	{
		ChangeState(BossMonsterState::AttackStay);
		return;
	}
}

void BossMonster::DamageStart()
{
	BossHp -= 5;
	ChangeAnimationState("BossMonster_Damage");
}

void BossMonster::DamageUpdate(float _Delta)
{
	if (0.5f <= GetLiveTime())
	{
		ChangeState(BossMonsterState::Idle);
		return;
	}
}

void BossMonster::AttackStayStart()
{
	ChangeAnimationState("BossMonster_AttackStay");
}

void BossMonster::AttackStayUpdate(float _Delta)
{
	if (0.2f <= GetLiveTime())
	{
		if (3 == Count)
		{
			Count = 0;
			ChangeState(BossMonsterState::Idle);
			return;

		}
		Count += 1;
		ChangeState(BossMonsterState::Attack);
		return;
	}
}

void BossMonster::AttackStart()
{
	BossAirAtt* StarAttack = GetLevel()->CreateActor<BossAirAtt>();
	StarAttack->SetPos(GetPos() + float4{ -10,60 });
	StarAttack->SetMaster(this);
	StarAttack->Init();

	Apple* AppleAtt = GetLevel()->CreateActor<Apple>();
	AppleAtt->SetGroundTexture(Kirby::GetMainPlayer()->GetGroundTexture());
	float RandX = GameEngineRandom::MainRandom.RandomFloat( 80.0f, 600.0f);
	float RandY = GameEngineRandom::MainRandom.RandomFloat( 200.0f, 360.0f);
	AppleAtt->SetPos(float4{ RandX, RandY });

	ChangeAnimationState("BossMonster_Attack");
}

void BossMonster::AttackUpdate(float _Delta)
{
	if (0.1f <= GetLiveTime())
	{
		ChangeState(BossMonsterState::AttackStay);
		return;
	}
}

