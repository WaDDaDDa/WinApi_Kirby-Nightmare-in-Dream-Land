#include "Star.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineLevel.h>

Star::Star()
{

}

Star::~Star()
{

}

void Star::Start()
{

	Renderer = CreateRenderer(RenderOrder::Play);
	{ // LeftAnimation 생성
		Renderer->CreateAnimation("StarAttack", "Star.bmp", 0, 1, 0.2f, true);
		Renderer->CreateAnimation("StarEffect", "StarEffects.bmp", 0, 3, 0.1f, true);
	}

	Renderer->ChangeAnimation("StarAttack");
	Renderer->SetScaleRatio(4.0f);

	AttackCollision = CreateCollision(CollisionOrder::PlayerAttack);
	AttackCollision->SetCollisionScale(AttackCollisionScale);
	AttackCollision->SetCollisionType(CollisionType::CirCle);
}


void Star::DirCheck()
{
	if (KirbyDir::Left == MainKirby->GetDir())
	{
		AddPos(LeftAttackPos);
		Dir = float4::LEFT;
	}
	else if (KirbyDir::Right == MainKirby->GetDir())
	{
		AddPos(RightAttackPos);
		Dir = float4::RIGHT;
	}
}

void Star::Update(float _Delta)
{
	AddPos(Dir * _Delta * Speed);

	// 1초뒤 데스
	if (1.0f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Death();
		}
	}

	std::vector<GameEngineCollision*> _Col;

	if (true == AttackCollision->Collision(CollisionOrder::MonsterBody
		, _Col
		, CollisionType::CirCle // 나를 사각형으로 봐줘
		, CollisionType::CirCle // 상대도 사각형으로 봐줘
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();
			Renderer->ChangeAnimation("StarEffect");
			Dir = float4::ZERO;
		}
	}

}