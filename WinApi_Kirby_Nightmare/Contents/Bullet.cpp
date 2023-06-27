#include "Bullet.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include "BurningMonster.h"
#include "Kirby.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

void Bullet::Start()
{

	Renderer = CreateRenderer(RenderOrder::Effect);
	Renderer->SetTexture("Blank.bmp");
	{ // LeftAnimation 생성
		Renderer->CreateAnimation("FireAttack", "BunringMonsterAttack.bmp", 0, 0, 0.2f, false);
		Renderer->CreateAnimation("FireEffect", "BunringMonsterAttack.bmp", 0, 3, 0.1f, false);
	}
	Renderer->ChangeAnimation("FireAttack");
	Renderer->SetScaleRatio(4.0f);

	AttackCollision = CreateCollision(CollisionOrder::MonsterFireAttack);
	AttackCollision->SetCollisionScale(AttackCollisionScale);
	AttackCollision->SetCollisionType(CollisionType::CirCle);

	SetOrder(UpdateOrder::Monster);
	ChangeState(BulletState::Normal);
}

void Bullet::Init()
{
	DirVec = Kirby::GetMainPlayer()->GetPos() - Master->GetPos();
	DirVec.Normalize();
}

void Bullet::DirCheck()
{
	if (BurningMonsterDir::Left == Master->GetDir())
	{
		AddPos(LeftAttackPos);
		Dir = float4::LEFT;
	}
	else if (BurningMonsterDir::Right == Master->GetDir())
	{
		AddPos(RightAttackPos);
		Dir = float4::RIGHT;
	}
}

void Bullet::Update(float _Delta)
{
	if (0.0f == GameEngineTime::MainTimer.GetTimeScale(GetOrder()))
	{
		return;
	}

	StateUpdate(_Delta);
}


void Bullet::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BulletState::Normal:
		return NormalUpdate(_Delta);
	case BulletState::Bomb:
		return BombUpdate(_Delta);
	default:
		break;
	}
}

void Bullet::ChangeState(BulletState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BulletState::Normal:
			NormalStart();
			break;
		case BulletState::Bomb:
			BombStart();
			break;
		default:
			break;
		}
	}
	ResetLiveTime();

	State = _State;
}

void Bullet::NormalStart()
{
	Renderer->ChangeAnimation("FireAttack");
}

void Bullet::NormalUpdate(float _Delta)
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
			ChangeState(BulletState::Bomb);
		}
	}
}

void Bullet::BombStart()
{
	Renderer->ChangeAnimation("FireEffect");
}

void Bullet::BombUpdate(float _Delta)
{
	if (0.4f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Death();
		}
	}
}
