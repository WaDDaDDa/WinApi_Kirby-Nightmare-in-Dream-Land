#include "BossAirAtt.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include "BurningMonster.h"
#include "Kirby.h"

BossAirAtt::BossAirAtt()
{

}

BossAirAtt::~BossAirAtt()
{

}

void BossAirAtt::Start()
{

	Renderer = CreateRenderer(RenderOrder::Effect);
	Renderer->SetTexture("Blank.bmp");
	{ // LeftAnimation 생성
		Renderer->CreateAnimation("BossAirAttack", "WoodAtt.bmp", 8, 11, 0.2f, true);
		Renderer->CreateAnimation("FireEffect", "BunringMonsterAttack.bmp", 0, 3, 0.1f, false);
	}
	Renderer->ChangeAnimation("BossAirAttack");
	Renderer->SetScaleRatio(4.0f);

	AttackCollision = CreateCollision(CollisionOrder::MonsterFireAttack);
	AttackCollision->SetCollisionScale(AttackCollisionScale);
	AttackCollision->SetCollisionType(CollisionType::CirCle);

	SetOrder(UpdateOrder::Monster);
	ChangeState(BossAirAttState::Normal);
}

void BossAirAtt::Init()
{
	DirVec = Kirby::GetMainPlayer()->GetPos() - Master->GetPos();
	DirVec.Normalize();
}

void BossAirAtt::DirCheck()
{
	AddPos(LeftAttackPos);
	Dir = float4::LEFT;
}

void BossAirAtt::Update(float _Delta)
{
	if (0.0f == GameEngineTime::MainTimer.GetTimeScale(GetOrder()))
	{
		return;
	}

	StateUpdate(_Delta);
}


void BossAirAtt::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BossAirAttState::Normal:
		return NormalUpdate(_Delta);
	case BossAirAttState::Bomb:
		return BombUpdate(_Delta);
	default:
		break;
	}
}

void BossAirAtt::ChangeState(BossAirAttState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BossAirAttState::Normal:
			NormalStart();
			break;
		case BossAirAttState::Bomb:
			BombStart();
			break;
		default:
			break;
		}
	}
	ResetLiveTime();

	State = _State;
}

void BossAirAtt::NormalStart()
{
	Renderer->ChangeAnimation("BossAirAttack");
}

void BossAirAtt::NormalUpdate(float _Delta)
{
	AddPos(DirVec * _Delta * Speed);

	// 1초뒤 데스
	if (2.0f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Death();
		}
	}

	std::vector<GameEngineCollision*> _Col;

	if (true == AttackCollision->Collision(CollisionOrder::PlayerBody
		, _Col
		, CollisionType::CirCle // 나를 사각형으로 봐줘
		, CollisionType::CirCle // 상대도 사각형으로 봐줘
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();
			ChangeState(BossAirAttState::Bomb);
		}
	}
}

void BossAirAtt::BombStart()
{
	Renderer->ChangeAnimation("FireEffect");
}

void BossAirAtt::BombUpdate(float _Delta)
{
	if (0.4f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Death();
		}
	}
}
