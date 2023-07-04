#include "BossMonster.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Kirby.h"
#include "BossAirAtt.h"
#include "Apple.h"
#include "WaddleDee.h"
#include "BurningMonster.h"
#include "SwordMan.h"
#include "SparkMonster.h"
#include "BGMPlayer.h"

void BossMonster::IdleStart()
{
	ChangeAnimationState("BossMonster_Idle");
}

void BossMonster::IdleUpdate(float _Delta)
{
	if (AttCoolTime <= 0.0f)
	{
		ChangeState(BossMonsterState::AttackStay);
		return;
	}
	else if (SpornAppleCoolTime <= 0.0f)
	{
		ChangeState(BossMonsterState::SpornApple);
		return;
	}

	//std::vector<GameEngineCollision*> _Col;

	//if (true == BodyCollision->Collision(CollisionOrder::BossAttack
	//	, _Col
	//	, CollisionType::Rect // 나의 충돌체 모양
	//	, CollisionType::CirCle // 상대의 충돌체 모양
	//))
	//{
	//	for (size_t i = 0; i < _Col.size(); i++)
	//	{
	//		GameEngineCollision* Collison = _Col[i];

	//		Actor = Collison->GetActor();

	//		float4 ActorPos = Actor->GetPos();

	//		Collison->Off();

	//		ChangeState(BossMonsterState::Damage);
	//		return;
	//	}
	//}
}

void BossMonster::DamageStart()
{
	Count = 0;
	SoundEffect = GameEngineSound::SoundPlay("song260.wav");
	ChangeAnimationState("BossMonster_Damage");
}

void BossMonster::DamageUpdate(float _Delta)
{
	if (0 >= BossHp)
	{
		ChangeState(BossMonsterState::Die);
	}

	if (1.0f <= GetLiveTime())
	{
		if (AttCoolTime <= 0.0f)
		{
			ChangeState(BossMonsterState::AttackStay);
			return;
		}
		else if (SpornAppleCoolTime <= 0.0f)
		{
			ChangeState(BossMonsterState::SpornApple);
			return;
		}
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
			AttCoolTime = 8.0f;
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

void BossMonster::SpornAppleStart()
{
	while (2 >= Count)
	{
		int RandValue = GameEngineRandom::MainRandom.RandomInt(0, 10);
		float RandX = GameEngineRandom::MainRandom.RandomFloat(80.0f, 600.0f);
		float RandY = GameEngineRandom::MainRandom.RandomFloat(200.0f, 360.0f);

		if (0 == RandValue)
		{
			WaddleDee* AppleAtt = GetLevel()->CreateActor<WaddleDee>();
			AppleAtt->SetGroundTexture(Kirby::GetMainPlayer()->GetGroundTexture());
			AppleAtt->SetPos(float4{ RandX, RandY });
		}
		else if (1 == RandValue)
		{
			BurningMonster* AppleAtt = GetLevel()->CreateActor<BurningMonster>();
			AppleAtt->SetGroundTexture(Kirby::GetMainPlayer()->GetGroundTexture());
			AppleAtt->SetPos(float4{ RandX, RandY });
		}
		else if (2 == RandValue)
		{
			SparkMonster* AppleAtt = GetLevel()->CreateActor<SparkMonster>();
			AppleAtt->SetGroundTexture(Kirby::GetMainPlayer()->GetGroundTexture());
			AppleAtt->SetPos(float4{ RandX, RandY });
		}
		else if (3 == RandValue)
		{
			SwordMan* AppleAtt = GetLevel()->CreateActor<SwordMan>();
			AppleAtt->SetGroundTexture(Kirby::GetMainPlayer()->GetGroundTexture());
			AppleAtt->SetPos(float4{ RandX, RandY });
		}
		else
		{
			Apple* AppleAtt = GetLevel()->CreateActor<Apple>();
			AppleAtt->SetGroundTexture(Kirby::GetMainPlayer()->GetGroundTexture());
			AppleAtt->SetPos(float4{ RandX, RandY });
		}

		Count += 1;
	}
	Count = 0;
	ChangeAnimationState("BossMonster_SpornApple");
}

void BossMonster::SpornAppleUpdate(float _Delta)
{
	if (3.0f <= GetLiveTime())
	{
		SpornAppleCoolTime = 12.0f;
		ChangeState(BossMonsterState::Idle);
		return;
	}
}

void BossMonster::DieStart()
{
	SoundEffect = GameEngineSound::SoundPlay("song227.wav");
	BodyCollision->Off();
	EffectRenderer1->ChangeAnimation("BossEndingEffect1");
	ChangeAnimationState("BossMonster_Die");
}

void BossMonster::DieUpdate(float _Delta)
{
	if (0.5f <= GetLiveTime())
	{
		EffectRenderer2->ChangeAnimation("BossEndingEffect2");
	}
	if (1.0f <= GetLiveTime())
	{
		EffectRenderer3->ChangeAnimation("BossEndingEffect3");
	}
	if (1.5f <= GetLiveTime())
	{
		EffectRenderer4->ChangeAnimation("BossEndingEffect4");
	}
	if (2.5f <= GetLiveTime())
	{
		BGMPlayer::ChangeBGM("song013 클리어 롱.wav", 0);
	}

}